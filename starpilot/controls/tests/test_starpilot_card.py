from types import SimpleNamespace

from opendbc.car.chrysler.values import CAR as CHRYSLER_CAR

from openpilot.starpilot.controls import starpilot_card as spc


class FakeParams:
  def __init__(self, *args, **kwargs):
    self._store = {}

  def get_bool(self, key):
    return bool(self._store.get(key, False))

  def put_bool(self, key, value):
    self._store[key] = bool(value)

  def get_int(self, key, default=0):
    return int(self._store.get(key, default))

  def put_int(self, key, value):
    self._store[key] = int(value)

  def put_bool_nonblocking(self, key, value):
    self.put_bool(key, value)


class FakeSM(dict):
  def __init__(self, *args, updated=None, **kwargs):
    super().__init__(*args, **kwargs)
    self.updated = updated or {}


def make_sm():
  return FakeSM({
    "carControl": SimpleNamespace(longActive=False),
    "selfdriveState": SimpleNamespace(active=False, alertType=[], experimentalMode=False),
    "starpilotSelfdriveState": SimpleNamespace(alertType=[]),
    "starpilotPlan": SimpleNamespace(lateralCheck=True),
    "liveCalibration": SimpleNamespace(calPerc=100),
  }, updated={"starpilotPlan": False})


def make_toggles(**overrides):
  defaults = {
    "always_on_lateral_lkas": False,
    "always_on_lateral_main": False,
    "always_on_lateral_pause_speed": 0.0,
    "bookmark_via_cancel": False,
    "bookmark_via_cancel_long": False,
    "bookmark_via_cancel_very_long": False,
    "bookmark_via_lkas": False,
    "conditional_experimental_mode": False,
    "experimental_mode_via_lkas": False,
    "force_coast_via_lkas": False,
    "lkas_allowed_for_aol": False,
    "pause_lateral_via_lkas": False,
    "pause_longitudinal_via_lkas": False,
    "speed_limit_controller": False,
    "switchback_mode_via_lkas": False,
    "traffic_mode_via_lkas": False,
  }
  defaults.update(overrides)
  return SimpleNamespace(**defaults)


def make_car_state(available=False, enabled=False, button_events=None):
  return SimpleNamespace(
    buttonEvents=button_events or [],
    cruiseState=SimpleNamespace(available=available, enabled=enabled),
    gearShifter=spc.GearShifter.drive,
    brakePressed=False,
    gasPressed=False,
    standstill=False,
    vEgo=15.0,
  )


def test_honda_lkas_button_can_toggle_always_on_lateral(monkeypatch, tmp_path):
  monkeypatch.setattr(spc, "Params", FakeParams)
  monkeypatch.setattr(spc, "is_FrogsGoMoo", lambda: False)
  monkeypatch.setattr(spc, "ERROR_LOGS_PATH", tmp_path)

  card = spc.StarPilotCard(SimpleNamespace(brand="honda"), SimpleNamespace(alternativeExperience=0))

  car_state = make_car_state(button_events=[SimpleNamespace(type=spc.ButtonType.lkas, pressed=True)])
  starpilot_car_state = SimpleNamespace(distancePressed=False)
  sm = make_sm()
  toggles = make_toggles(always_on_lateral_lkas=True, lkas_allowed_for_aol=True)

  ret = card.update(car_state, starpilot_car_state, sm, toggles)

  assert ret.alwaysOnLateralAllowed is True
  assert ret.pauseLateral is False


def test_honda_lkas_button_pauses_lateral_when_cruise_is_active(monkeypatch, tmp_path):
  monkeypatch.setattr(spc, "Params", FakeParams)
  monkeypatch.setattr(spc, "is_FrogsGoMoo", lambda: False)
  monkeypatch.setattr(spc, "ERROR_LOGS_PATH", tmp_path)

  card = spc.StarPilotCard(
    SimpleNamespace(brand="honda"),
    SimpleNamespace(alternativeExperience=spc.ALTERNATIVE_EXPERIENCE.ALWAYS_ON_LATERAL),
  )
  card.always_on_lateral_allowed = True

  car_state = make_car_state(available=True, enabled=True, button_events=[SimpleNamespace(type=spc.ButtonType.lkas, pressed=True)])
  starpilot_car_state = SimpleNamespace(distancePressed=False)
  sm = make_sm()
  sm["selfdriveState"].active = True
  toggles = make_toggles(always_on_lateral_lkas=True, lkas_allowed_for_aol=True)

  ret = card.update(car_state, starpilot_car_state, sm, toggles)

  assert ret.alwaysOnLateralAllowed is False
  assert ret.pauseLateral is True

  ret = card.update(car_state, starpilot_car_state, sm, toggles)

  assert ret.alwaysOnLateralAllowed is True
  assert ret.pauseLateral is False


def test_main_aol_still_follows_cruise_main_for_other_platforms(monkeypatch, tmp_path):
  monkeypatch.setattr(spc, "Params", FakeParams)
  monkeypatch.setattr(spc, "is_FrogsGoMoo", lambda: False)
  monkeypatch.setattr(spc, "ERROR_LOGS_PATH", tmp_path)

  card = spc.StarPilotCard(SimpleNamespace(brand="toyota", carFingerprint="TOYOTA_TEST", pcmCruise=True),
                           SimpleNamespace(alternativeExperience=spc.ALTERNATIVE_EXPERIENCE.ALWAYS_ON_LATERAL))

  ret = card.update(make_car_state(available=True), SimpleNamespace(distancePressed=False), make_sm(),
                    make_toggles(always_on_lateral_main=True))

  assert ret.alwaysOnLateralAllowed is True
  assert ret.alwaysOnLateralEnabled is True


def test_pacifica_hybrid_main_aol_waits_for_set_press(monkeypatch, tmp_path):
  monkeypatch.setattr(spc, "Params", FakeParams)
  monkeypatch.setattr(spc, "is_FrogsGoMoo", lambda: False)
  monkeypatch.setattr(spc, "ERROR_LOGS_PATH", tmp_path)

  card = spc.StarPilotCard(
    SimpleNamespace(brand="chrysler", carFingerprint=CHRYSLER_CAR.CHRYSLER_PACIFICA_2019_HYBRID, pcmCruise=True),
    SimpleNamespace(alternativeExperience=spc.ALTERNATIVE_EXPERIENCE.ALWAYS_ON_LATERAL),
  )

  sm = make_sm()
  toggles = make_toggles(always_on_lateral_main=True)
  starpilot_car_state = SimpleNamespace(distancePressed=False)
  car_state = make_car_state(available=True, enabled=False)

  ret = card.update(car_state, starpilot_car_state, sm, toggles)
  assert ret.alwaysOnLateralAllowed is False
  assert ret.alwaysOnLateralEnabled is False

  car_state.cruiseState.enabled = True
  ret = card.update(car_state, starpilot_car_state, sm, toggles)
  assert ret.alwaysOnLateralAllowed is True
  assert ret.alwaysOnLateralEnabled is True

  car_state.cruiseState.enabled = False
  ret = card.update(car_state, starpilot_car_state, sm, toggles)
  assert ret.alwaysOnLateralAllowed is True
  assert ret.alwaysOnLateralEnabled is True

  car_state.cruiseState.available = False
  ret = card.update(car_state, starpilot_car_state, sm, toggles)
  assert ret.alwaysOnLateralAllowed is False
  assert ret.alwaysOnLateralEnabled is False


def _make_distance_card(monkeypatch, tmp_path):
  monkeypatch.setattr(spc, "Params", FakeParams)
  monkeypatch.setattr(spc, "is_FrogsGoMoo", lambda: False)
  monkeypatch.setattr(spc, "ERROR_LOGS_PATH", tmp_path)
  card = spc.StarPilotCard(SimpleNamespace(brand="hyundai"), SimpleNamespace(alternativeExperience=0))
  calls = []
  monkeypatch.setattr(card, "handle_button_event", lambda key, sm, toggles: calls.append(key))
  return card, calls


def _press_distance(card, frames):
  sm = make_sm()
  toggles = make_toggles()
  for pressed in frames:
    card.update(make_car_state(), SimpleNamespace(distancePressed=pressed), sm, toggles)


def test_distance_short_press_fires_once_on_debounced_release(monkeypatch, tmp_path):
  card, calls = _make_distance_card(monkeypatch, tmp_path)
  # Held 20 frames, then released and held low long enough to debounce.
  _press_distance(card, [True] * 20 + [False] * spc.GAP_RELEASE_DEBOUNCE)
  assert calls == ["distance"]


def test_distance_single_frame_glitch_does_not_fire_phantom_short_press(monkeypatch, tmp_path):
  card, calls = _make_distance_card(monkeypatch, tmp_path)
  # One dropped frame mid-hold must not register as a release.
  frames = [True] * 20 + [False] + [True] * 40 + [False] * spc.GAP_RELEASE_DEBOUNCE
  _press_distance(card, frames)
  # 60 held frames > long_press_threshold (50): this is a long press, not short, and fires once.
  assert calls == ["distance_long"]


def test_distance_long_press_does_not_also_fire_short(monkeypatch, tmp_path):
  card, calls = _make_distance_card(monkeypatch, tmp_path)
  _press_distance(card, [True] * spc.CRUISE_LONG_PRESS + [False] * spc.GAP_RELEASE_DEBOUNCE)
  assert calls == ["distance_long"]


def test_cancel_button_short_press_can_run_independent_mapping(monkeypatch, tmp_path):
  monkeypatch.setattr(spc, "Params", FakeParams)
  monkeypatch.setattr(spc, "is_FrogsGoMoo", lambda: False)
  monkeypatch.setattr(spc, "ERROR_LOGS_PATH", tmp_path)

  card = spc.StarPilotCard(SimpleNamespace(brand="gm"), SimpleNamespace(alternativeExperience=0))
  sm = make_sm()
  toggles = make_toggles(bookmark_via_cancel=True)
  starpilot_car_state = SimpleNamespace(distancePressed=False, cancelPressed=False)

  card.update(make_car_state(), starpilot_car_state, sm, toggles)
  assert card.params_memory.get_int("WheelButtonBookmarkCounter") == 0

  starpilot_car_state.cancelPressed = True
  ret = card.update(make_car_state(), starpilot_car_state, sm, toggles)
  assert ret.cancelLongPressed is False
  assert ret.cancelVeryLongPressed is False
  assert card.params_memory.get_int("WheelButtonBookmarkCounter") == 0

  starpilot_car_state.cancelPressed = False
  ret = card.update(make_car_state(), starpilot_car_state, sm, toggles)
  assert ret.cancelLongPressed is False
  assert ret.cancelVeryLongPressed is False
  assert card.params_memory.get_int("WheelButtonBookmarkCounter") == 1
