import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID

from .. import CONF_C4002_ID, C4002Component, dfrobot_c4002_ns

C4002TextSensorHub = dfrobot_c4002_ns.class_("C4002TextSensorHub", cg.Component)

C4002_TEXT_SENSOR = "c4002_text_sensor"
CONF_ACTIVE_GATES_SUMMARY = "active_gates_summary"
CONF_MOVEMENT_DIRECTION = "movement_direction"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(C4002TextSensorHub),
        cv.GenerateID(CONF_C4002_ID): cv.use_id(C4002Component),
        cv.Optional(C4002_TEXT_SENSOR): text_sensor.text_sensor_schema(
            icon="mdi:message-text-outline"
        ),
        cv.Optional(CONF_ACTIVE_GATES_SUMMARY): text_sensor.text_sensor_schema(
            icon="mdi:radar"
        ),
        cv.Optional(CONF_MOVEMENT_DIRECTION): text_sensor.text_sensor_schema(
            icon="mdi:directions"
        ),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    hub = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(hub, config)

    parent = await cg.get_variable(config[CONF_C4002_ID])
    cg.add(hub.set_parent(parent))

    if C4002_TEXT_SENSOR in config:
        ts = await text_sensor.new_text_sensor(config[C4002_TEXT_SENSOR])
        cg.add(parent.set_text_sensor(ts))
        cg.add(hub.set_text_sensor(ts))

    if CONF_ACTIVE_GATES_SUMMARY in config:
        ts_summary = await text_sensor.new_text_sensor(
            config[CONF_ACTIVE_GATES_SUMMARY]
        )
        cg.add(hub.set_active_gates_summary_sensor(ts_summary))

    if CONF_MOVEMENT_DIRECTION in config:
        ts_dir = await text_sensor.new_text_sensor(
            config[CONF_MOVEMENT_DIRECTION]
        )
        cg.add(hub.set_movement_direction_sensor(ts_dir))
