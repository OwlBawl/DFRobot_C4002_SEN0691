import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID, DEVICE_CLASS_OCCUPANCY

from .. import CONF_C4002_ID, C4002Component, dfrobot_c4002_ns

C4002BinarySensorHub = dfrobot_c4002_ns.class_(
    "C4002BinarySensorHub", cg.Component
)

GATE_SCHEMA = binary_sensor.binary_sensor_schema(
    device_class=DEVICE_CLASS_OCCUPANCY,
    icon="mdi:radar",
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(C4002BinarySensorHub),
        cv.Required(CONF_C4002_ID): cv.use_id(C4002Component),
        **{cv.Optional(f"gate_{i}"): GATE_SCHEMA for i in range(15)},
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    hub = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(hub, config)

    c4002 = await cg.get_variable(config[CONF_C4002_ID])
    cg.add(hub.set_parent(c4002))

    for i in range(15):
        key = f"gate_{i}"
        if key in config:
            bs = await binary_sensor.new_binary_sensor(config[key])
            cg.add(hub.set_gate_binary_sensor(i, bs))
