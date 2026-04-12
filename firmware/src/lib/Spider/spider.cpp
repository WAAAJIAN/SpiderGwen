#include "spider.h"

void Spider::init(ST3215_driver &driver, uint8_t *coxa_ids, uint8_t *femur_ids, uint8_t *tibia_ids)
{
    _driver = &driver;

    for (uint8_t i = 0; i < NUM_LEGS; i++)
        _legs[i] = new Leg(coxa_ids[i], femur_ids[i], tibia_ids[i]);

    _initialised = true;
}

bool Spider::ping_all()
{
    if (!_initialised)
        return false;

    bool all_ok = true;

    for (uint8_t i = 0; i < NUM_LEGS; i++)
    {
        uint8_t coxa_id  = 0;
        uint8_t femur_id = 0;
        uint8_t tibia_id = 0;
        _legs[i]->get_ids(coxa_id, femur_id, tibia_id);

        if (!_driver->ping(coxa_id))
        {
            all_ok = false;
        }
        if (!_driver->ping(femur_id))
        {
            all_ok = false;
        }
        if (!_driver->ping(tibia_id))
        {
            all_ok = false;
        }
    }

    return all_ok;
}

void Spider::set_foot(uint8_t leg_index, float x, float y, float z)
{
    if (!_initialised || leg_index >= NUM_LEGS) 
    {
        return;
    }

    _legs[leg_index]->set_foot(x, y, z);
}

void Spider::execute_movements(uint16_t speed)
{
    if (!_initialised) 
    {
        return;
    }

    // validate all legs before touching the bus
    for (uint8_t i = 0; i < NUM_LEGS; i++)
    {
        if (!_legs[i]->is_ik_valid())
        {
            return;
        }
    }

    uint8_t  ids[NUM_SERVOS];
    uint16_t angles[NUM_SERVOS];
    uint16_t speeds[NUM_SERVOS];

    for (uint8_t i = 0; i < NUM_LEGS; i++)
    {
        uint8_t coxa_id, femur_id, tibia_id;
        _legs[i]->get_ids(coxa_id, femur_id, tibia_id);

        float a, b, c;
        _legs[i]->get_angles(a, b, c);

        ids[i * JOINTS_PER_LEG]     = coxa_id;
        ids[i * JOINTS_PER_LEG + 1] = femur_id;
        ids[i * JOINTS_PER_LEG + 2] = tibia_id;

        angles[i * JOINTS_PER_LEG]     = (uint16_t)a;
        angles[i * JOINTS_PER_LEG + 1] = (uint16_t)b;
        angles[i * JOINTS_PER_LEG + 2] = (uint16_t)c;

        speeds[i * JOINTS_PER_LEG]     = speed;
        speeds[i * JOINTS_PER_LEG + 1] = speed;
        speeds[i * JOINTS_PER_LEG + 2] = speed;
    }

    _driver->set_angle_speed_sync(ids, angles, speeds, NUM_SERVOS);
}

void Spider::stand(uint16_t speed)
{
    if (!_initialised)
        return;

    static constexpr int STAND_STEPS = 50;

    // step 1 — move to crouched foot position
    for (uint8_t i = 0; i < NUM_LEGS; i++)
        _legs[i]->set_foot(0.0f, 200.0f, 70.0f);
    execute_movements(speed);
    delay(1000);

    // step 2 — gradually remove the angle offset while keeping foot at (0, 200, 70)
    for (int current_step = 0; current_step < STAND_STEPS; current_step++)
    {
        float d = 20.0f - (20.0f / STAND_STEPS) * current_step;

        uint8_t  ids[NUM_SERVOS];
        uint16_t angles[NUM_SERVOS];
        uint16_t speeds[NUM_SERVOS];

        for (uint8_t i = 0; i < NUM_LEGS; i++)
        {
            // IK runs on crouched position every iteration
            _legs[i]->set_foot(0.0f, 200.0f, 70.0f);

            uint8_t coxa_id, femur_id, tibia_id;
            _legs[i]->get_ids(coxa_id, femur_id, tibia_id);

            float a, b, c;
            _legs[i]->get_angles(a, b, c);

            // apply decreasing offset on top of IK result
            b = constrain(b + d, FEMUR_MIN, FEMUR_MAX);
            c = constrain(c + d, TIBIA_MIN, TIBIA_MAX);

            ids[i * JOINTS_PER_LEG]     = coxa_id;
            ids[i * JOINTS_PER_LEG + 1] = femur_id;
            ids[i * JOINTS_PER_LEG + 2] = tibia_id;

            angles[i * JOINTS_PER_LEG]     = (uint16_t)a;
            angles[i * JOINTS_PER_LEG + 1] = (uint16_t)b;
            angles[i * JOINTS_PER_LEG + 2] = (uint16_t)c;

            speeds[i * JOINTS_PER_LEG]     = speed;
            speeds[i * JOINTS_PER_LEG + 1] = speed;
            speeds[i * JOINTS_PER_LEG + 2] = speed;
        }

        _driver->set_angle_speed_sync(ids, angles, speeds, NUM_SERVOS);
        delay(40);
    }
}

void Spider::balance(float pitch, float roll, uint16_t speed)
{
    if (!_initialised) 
    {
        return;
    }

    float dx = pitch * 2.0f;
    float dy = roll  * 2.0f;

    for (uint8_t i = 0; i < NUM_LEGS; i++)
    {
        _legs[i]->set_foot(X_OFFSET + dx, Y_OFFSET + dy, Z_OFFSET);
    }

    execute_movements(speed);
}

void Spider::enable_torque(bool enable)
{
    if (!_initialised)
    {
        return;
    };

    for (uint8_t i = 1; i <= NUM_SERVOS; i++)
    {
        _driver->set_torque(i, enable);
    }
}

void Spider::estop()
{
    if (!_driver) 
    {
        return;  // bypass initialisation check — safety critical
    }

    for (uint8_t i = 1; i <= NUM_SERVOS; i++)
    {
        _driver->set_torque(i, false);
    }

    Serial.println("⚠ ESTOP — all torque disabled");
}

bool Spider::read_all_angles(uint16_t *angles)
{
    if (!_initialised) 
    {
        return false;
    }

    bool all_ok = true;
    for (uint8_t i = 0; i < NUM_LEGS; i++)
    {
        uint8_t coxa_id, femur_id, tibia_id;
        _legs[i]->get_ids(coxa_id, femur_id, tibia_id);

        uint8_t ids[JOINTS_PER_LEG] = 
        { 
            coxa_id, 
            femur_id, 
            tibia_id 
        };

        for (uint8_t j = 0; j < JOINTS_PER_LEG; j++)
        {
            uint16_t angle = 0;
            if (_driver->read_angle(ids[j], &angle))
                angles[i * JOINTS_PER_LEG + j] = angle;
            else
            {
                angles[i * JOINTS_PER_LEG + j] = 0xFFFF;
                all_ok = false;
            }
        }
    }
    return all_ok;
}

bool Spider::read_all_status(uint8_t *statuses)
{
    if (!_initialised) 
    {
        return false;
    }

    bool all_ok = true;
    for (uint8_t i = 0; i < NUM_LEGS; i++)
    {
        uint8_t coxa_id, femur_id, tibia_id;
        _legs[i]->get_ids(coxa_id, femur_id, tibia_id);

        uint8_t ids[JOINTS_PER_LEG] = 
        { 
            coxa_id, 
            femur_id, 
            tibia_id 
        };

        for (uint8_t j = 0; j < JOINTS_PER_LEG; j++)
        {
            uint8_t status = 0;
            if (_driver->read_status(ids[j], &status))
            {
                statuses[i * JOINTS_PER_LEG + j] = status;
                if (status != 0x00) 
                {
                    all_ok = false;
                }
            }
            else
            {
                statuses[i * JOINTS_PER_LEG + j] = 0xFF;
                all_ok = false;
            }
        }
    }
    return all_ok;
}