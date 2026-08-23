import esphome.codegen as cg
from esphome.components import select
import esphome.config_validation as cv
from esphome.const import CONF_OPTIONS, ENTITY_CATEGORY_CONFIG, ICON_ACCOUNT

from .. import CONF_C4002_ID, C4002Component, dfrobot_c4002_ns

C4002Select = dfrobot_c4002_ns.class_("C4002Select", select.Select, cg.Component)
MotionSensitivitySelect = dfrobot_c4002_ns.class_(
    "MotionSensitivitySelect", select.Select, cg.Component
)
PresenceSensitivitySelect = dfrobot_c4002_ns.class_(
    "PresenceSensitivitySelect", select.Select, cg.Component
)
ResolutionModeSelect = dfrobot_c4002_ns.class_(
    "ResolutionModeSelect", select.Select, cg.Component
)
GateSelect = dfrobot_c4002_ns.class_("GateSelect", select.Select, cg.Component)

OPERATING_MODE_OPTIONS = ["Motion Only", "Presence Only", "Motion OR Presence"]
SENSITIVITY_OPTIONS = ["Low", "Medium", "High", "Custom"]
RESOLUTION_OPTIONS = ["80cm", "20cm"]
GATE_OPTIONS = [
    "Gate 0 (0.2m)",
    "Gate 1 (0.8m)",
    "Gate 2 (1.6m)",
    "Gate 3 (2.4m)",
    "Gate 4 (3.2m)",
    "Gate 5 (4.0m)",
    "Gate 6 (4.8m)",
    "Gate 7 (5.6m)",
    "Gate 8 (6.4m)",
    "Gate 9 (7.2m)",
    "Gate 10 (8.0m)",
    "Gate 11 (8.8m)",
    "Gate 12 (9.6m)",
    "Gate 13 (10.4m)",
    "Gate 14 (11.2m)",
]

CONF_OPERATING_MODE = "operating_mode"
CONF_MOTION_SENSITIVITY = "motion_sensitivity"
CONF_PRESENCE_SENSITIVITY = "presence_sensitivity"
CONF_RESOLUTION_MODE = "resolution_mode"
CONF_GATE_SELECTOR = "gate_selector"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_C4002_ID): cv.use_id(C4002Component),
        cv.Optional(CONF_OPERATING_MODE): select.select_schema(
            C4002Select,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon=ICON_ACCOUNT,
        ).extend(
            {
                cv.Optional(CONF_OPTIONS, default=OPERATING_MODE_OPTIONS): cv.All(
                    cv.ensure_list(cv.string_strict), cv.Length(min=1, max=3)
                ),
            }
        ),
        cv.Optional(CONF_MOTION_SENSITIVITY): select.select_schema(
            MotionSensitivitySelect,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:tune",
        ),
        cv.Optional(CONF_PRESENCE_SENSITIVITY): select.select_schema(
            PresenceSensitivitySelect,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:tune-vertical",
        ),
        cv.Optional(CONF_RESOLUTION_MODE): select.select_schema(
            ResolutionModeSelect,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:grid",
        ),
        cv.Optional(CONF_GATE_SELECTOR): select.select_schema(
            GateSelect,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:ray-start-arrow",
        ),
    }
)


async def to_code(config):
    c4002_component = await cg.get_variable(config[CONF_C4002_ID])

    # OUT Mode
    if operating_mode_config := config.get(CONF_OPERATING_MODE):
        options = operating_mode_config.get(CONF_OPTIONS, OPERATING_MODE_OPTIONS)
        operating_mode_select = await select.new_select(
            operating_mode_config, options=options
        )
        await cg.register_parented(operating_mode_select, config[CONF_C4002_ID])
        cg.add(c4002_component.set_operating_mode_select(operating_mode_select))

    # Motion Sensitivity
    if motion_sens_config := config.get(CONF_MOTION_SENSITIVITY):
        motion_sens_select = await select.new_select(
            motion_sens_config, options=SENSITIVITY_OPTIONS
        )
        await cg.register_parented(motion_sens_select, config[CONF_C4002_ID])
        cg.add(c4002_component.set_motion_sensitivity_select(motion_sens_select))

    # Presence Sensitivity
    if presence_sens_config := config.get(CONF_PRESENCE_SENSITIVITY):
        presence_sens_select = await select.new_select(
            presence_sens_config, options=SENSITIVITY_OPTIONS
        )
        await cg.register_parented(presence_sens_select, config[CONF_C4002_ID])
        cg.add(c4002_component.set_presence_sensitivity_select(presence_sens_select))

    # Resolution Mode
    if resolution_config := config.get(CONF_RESOLUTION_MODE):
        res_select = await select.new_select(
            resolution_config, options=RESOLUTION_OPTIONS
        )
        await cg.register_parented(res_select, config[CONF_C4002_ID])
        cg.add(c4002_component.set_resolution_mode_select(res_select))

    # Gate Selector
    if gate_select_config := config.get(CONF_GATE_SELECTOR):
        g_select = await select.new_select(gate_select_config, options=GATE_OPTIONS)
        await cg.register_parented(g_select, config[CONF_C4002_ID])
        cg.add(c4002_component.set_gate_select(g_select))
