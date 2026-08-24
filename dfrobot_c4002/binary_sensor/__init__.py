import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID, DEVICE_CLASS_MOTION, DEVICE_CLASS_OCCUPANCY

from .. import CONF_C4002_ID, C4002Component, dfrobot_c4002_ns

C4002BinarySensorHub = dfrobot_c4002_ns.class_(
    "C4002BinarySensorHub", cg.Component
)

CONF_MOTION = "motion"
CONF_PRESENCE = "presence"

GATE_SCHEMA = binary_sensor.binary_sensor_schema(
    device_class=DEVICE_CLASS_OCCUPANCY,
    icon="mdi:radar",
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(C4002BinarySensorHub),
        cv.Required(CONF_C4002_ID): cv.use_id(C4002Component),
        cv.Optional(CONF_MOTION): binary_sensor.binary_sensor_schema(
            device_class=DEVICE_CLASS_MOTION,
            icon="mdi:motion-sensor",
        ),
        cv.Optional(CONF_PRESENCE): binary_sensor.binary_sensor_schema(
            device_class=DEVICE_CLASS_OCCUPANCY,
            icon="mdi:home-account",
        ),
        **{cv.Optional(f"gate_{i}"): GATE_SCHEMA for i in range(15)},
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    hub = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(hub, config)

    c4002 = await cg.get_variable(config[CONF_C4002_ID])
    cg.add(hub.set_parent(c4002))

    if motion_config := config.get(CONF_MOTION):
        sens_motion = await binary_sensor.new_binary_sensor(motion_config)
        cg.add(hub.set_motion_binary_sensor(sens_motion))

    if presence_config := config.get(CONF_PRESENCE):
        sens_presence = await binary_sensor.new_binary_sensor(presence_config)
        cg.add(hub.set_presence_binary_sensor(sens_presence))

    for i in range(15):
        key = f"gate_{i}"
        if key in config:
            bs = await binary_sensor.new_binary_sensor(config[key])
            cg.add(hub.set_gate_binary_sensor(i, bs))
