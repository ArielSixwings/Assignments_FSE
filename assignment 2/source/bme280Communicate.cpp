#include "../includes/bme280Communicate.h"

bme280Communicate::bme280Communicate() {
	rslt = BME280_OK;

	if ((id.fd = open("/dev/i2c-1", O_RDWR)) < 0){
		fprintf(stderr, "Failed to open the i2c bus %s\n", "/dev/i2c-1");
		exit(1);
	}

	id.dev_addr = BME280_I2C_ADDR_PRIM;

	if (ioctl(id.fd, I2C_SLAVE, id.dev_addr) < 0){
		fprintf(stderr, "Failed to acquire bus access and/or talk to slave.\n");
		exit(1);
	}

	dev.intf = BME280_I2C_INTF;
	dev.read = user_i2c_read;
	dev.write = user_i2c_write;
	dev.delay_us = user_delay_us;

	dev.intf_ptr = &id;

	rslt = bme280_init(&dev);
	if (rslt != BME280_OK){
		fprintf(stderr, "Failed to initialize the device (code %+d).\n", rslt);
		exit(1);
	}
}

bme280Communicate::~bme280Communicate() = default;

void user_delay_us(uint32_t period, void *intf_ptr) {
	struct identifier id;
	id = *((struct identifier *)intf_ptr);
	usleep(period);
}

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr) {
	struct identifier id;

	id = *((struct identifier *)intf_ptr);

	write(id.fd, &reg_addr, 1);
	read(id.fd, data, len);

	return 0;
}

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr) {
	uint8_t *buf;
	struct identifier id;

	id = *((struct identifier *)intf_ptr);

	buf = (uint8_t *)malloc(len + 1);
	buf[0] = reg_addr;
	memcpy(buf + 1, data, len);
	if (write(id.fd, buf, len + 1) < (uint16_t)len)
	{
		return BME280_E_COMM_FAIL;
	}

	free(buf);

	return BME280_OK;
}