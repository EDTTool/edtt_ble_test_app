/**
 * Copyright (c) 2019 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/**
 * @brief Service B.1
 *
 *  This code is auto-generated from the Excel Workbook
 *  'GATT_Test_Databases.xlsm' Sheet: 'Large Database 2'
 */

#include <sys/byteorder.h>
#include <sys/printk.h>

#include <bluetooth/gatt.h>

#include "gatt_macs.h"

/** @def BT_UUID_SERVICE_B_1
 *  @brief UUID for the Service B.1
 */
#define BT_UUID_SERVICE_B_1             BT_UUID_DECLARE_16(0xa00b)

/** @def BT_UUID_VALUE_V4
 *  @brief UUID for the Value V4 Characteristic
 */
#define BT_UUID_VALUE_V4                BT_UUID_DECLARE_16(0xb004)

static u8_t   value_v4_value = 0x04;

/**
 * @brief Attribute read call back for the Value V4 attribute
 *
 * @param conn   The connection that is requesting to read
 * @param attr   The attribute that's being read
 * @param buf    Buffer to place the read result in
 * @param len    Length of data to read
 * @param offset Offset to start reading from
 *
 * @return       Number of bytes read, or in case of an error -
 *               BT_GATT_ERR() with a specific ATT error code.
 */
static ssize_t read_value_v4(struct bt_conn *conn,
			     const struct bt_gatt_attr *attr, void *buf,
			     u16_t len, u16_t offset)
{
	const u8_t *value = attr->user_data;

	return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
				 sizeof(value_v4_value));
}

/**
 * @brief Attribute write call back for the Value V4 attribute
 *
 * @param conn   The connection that is requesting to write
 * @param attr   The attribute that's being written
 * @param buf    Buffer with the data to write
 * @param len    Number of bytes in the buffer
 * @param offset Offset to start writing from
 * @param flags  Flags (BT_GATT_WRITE_*)
 *
 * @return       Number of bytes written, or in case of an error -
 *               BT_GATT_ERR() with a specific ATT error code.
 */
static ssize_t write_value_v4(struct bt_conn *conn,
			      const struct bt_gatt_attr *attr, const void *buf,
			      u16_t len, u16_t offset, u8_t flags)
{
	u8_t *value = attr->user_data;

	if (offset >= sizeof(value_v4_value))
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	if (offset + len > sizeof(value_v4_value))
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);

	memcpy(value + offset, buf, len);

	return len;
}

#define BT_GATT_CHRC_NONE 0

struct bt_gatt_attr service_b_1_2_attrs[] = {
	BT_GATT_PRIMARY_SERVICE(BT_UUID_SERVICE_B_1, 0x50),
	BT_GATT_CHARACTERISTIC(BT_UUID_VALUE_V4,
		BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE,
		BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
		read_value_v4, write_value_v4, &value_v4_value, 0x51)
};

static struct bt_gatt_service service_b_1_2_svc =
			BT_GATT_SERVICE(service_b_1_2_attrs);

/**
 * @brief Register the Service B.1 and all its Characteristics...
 */
void service_b_1_2_init(void)
{
	bt_gatt_service_register(&service_b_1_2_svc);
}

/**
 * @brief Un-Register the Service B.1 and all its Characteristics...
 */
void service_b_1_2_remove(void)
{
	bt_gatt_service_unregister(&service_b_1_2_svc);
}
