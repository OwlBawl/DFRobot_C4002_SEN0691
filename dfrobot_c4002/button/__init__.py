import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import (
    DEVICE_CLASS_RESTART,
    ENTITY_CATEGORY_CONFIG,
)

from .. import CONF_C4002_ID, C4002Component, dfrobot_c4002_ns

C4002RefreshButton = dfrobot_c4002_ns.class_(
    "C4002RefreshButton", button.Button, cg.Component
)
C4002FactoryResetButton = dfrobot_c4002_ns.class_(
    "C4002FactoryResetButton", button.Button, cg.Component
)
C4002FactoryReset2Button = dfrobot_c4002_ns.class_(
    "C4002FactoryReset2Button", button.Button, cg.Component
)

CONF_REFRESH_PARAMETERS = "refresh_parameters"
CONF_FACTORY_RESET = "factory_reset"
CONF_FACTORY_RESET_2 = "factory_reset_2"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_C4002_ID): cv.use_id(C4002Component),
        cv.Optional(CONF_REFRESH_PARAMETERS): button.button_schema(
            C4002RefreshButton,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:refresh",
        ),
        cv.Optional(CONF_FACTORY_RESET): button.button_schema(
            C4002FactoryResetButton,
            device_class=DEVICE_CLASS_RESTART,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:restore",
        ),
        cv.Optional(CONF_FACTORY_RESET_2): button.button_schema(
            C4002FactoryReset2Button,
            device_class=DEVICE_CLASS_RESTART,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:restore-alert",
        ),
    }
)


async def to_code(config):
    if refresh_config := config.get(CONF_REFRESH_PARAMETERS):
        b = await button.new_button(refresh_config)
        await cg.register_parented(b, config[CONF_C4002_ID])

    if factory_reset_config := config.get(CONF_FACTORY_RESET):
        b = await button.new_button(factory_reset_config)
        await cg.register_parented(b, config[CONF_C4002_ID])

    if factory_reset_2_config := config.get(CONF_FACTORY_RESET_2):
        b = await button.new_button(factory_reset_2_config)
        await cg.register_parented(b, config[CONF_C4002_ID])
