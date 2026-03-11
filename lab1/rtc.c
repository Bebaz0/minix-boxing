#include "rtc.h"
#include <lcom/lcf.h>
#include <minix/syslib.h>

#define TODO return -1

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_REG_A 0x0A
#define RTC_REG_B 0x0B
#define RTC_REG_DAY 0x07
#define RTC_REG_MONTH 0x08
#define RTC_REG_YEAR 0x09
#define RTC_UIP_MSK (1 << 7)
#define RTC_DM_MSK (1 << 2)

static int bcd_to_bin(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

static int rtc_read_reg(uint8_t reg, uint8_t *value) {
    uint32_t temp;

    if (sys_outb(RTC_ADDR_REG, reg) != 0) return 1; // escolhe o registo
    if (sys_inb(RTC_DATA_REG, &temp) != 0) return 1; // lê o valor do registo

    *value = (uint8_t) temp;
    return 0;
}

int rtc_read_date(rtc_date *date) {
  if (date == NULL) return -1;

  uint8_t reg_a, reg_b;
  uint8_t day, month, year;

  if (rtc_read_reg(RTC_REG_A, &reg_a) != 0) return 1;

  while (reg_a & RTC_UIP_MSK) {
    tickdelay(micros_to_ticks(500));
    if (rtc_read_reg(RTC_REG_A, &reg_a) != 0) return 1;
  } 

  if (rtc_read_reg(RTC_REG_B, &reg_b ) != 0) return 1;
  if (rtc_read_reg(RTC_REG_DAY, &day) != 0) return 1;
  if (rtc_read_reg(RTC_REG_MONTH, &month) != 0) return 1;
  if (rtc_read_reg(RTC_REG_YEAR, &year) != 0) return 1;

  if ((reg_b & RTC_DM_MSK) == 0) {
    day = bcd_to_bin(day);
    month = bcd_to_bin(month);
    year = bcd_to_bin(year);
  }

  date->day = day;
  date->month = month;
  date->year = year;

  return 0;
}
