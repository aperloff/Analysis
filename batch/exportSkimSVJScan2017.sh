#!/bin/bash

export SAMPLES=(
SVJ_1500_100_0.3_peak_MC2017 \
SVJ_1500_10_0.3_peak_MC2017 \
SVJ_1500_1_0.3_peak_MC2017 \
SVJ_1500_20_0.1_peak_MC2017 \
SVJ_1500_20_0.2_peak_MC2017 \
SVJ_1500_20_0.3_high_MC2017 \
SVJ_1500_20_0.3_low_MC2017 \
SVJ_1500_20_0.3_peak_MC2017 \
SVJ_1500_20_0.4_peak_MC2017 \
SVJ_1500_20_0.5_peak_MC2017 \
SVJ_1500_20_0.6_peak_MC2017 \
SVJ_1500_20_0.7_peak_MC2017 \
SVJ_1500_20_0.8_peak_MC2017 \
SVJ_1500_20_0.9_peak_MC2017 \
SVJ_1500_20_0_peak_MC2017 \
SVJ_1500_20_1_peak_MC2017 \
SVJ_1500_30_0.3_peak_MC2017 \
SVJ_1500_40_0.3_peak_MC2017 \
SVJ_1500_50_0.3_peak_MC2017 \
SVJ_1500_5_0.3_peak_MC2017 \
SVJ_1500_60_0.3_peak_MC2017 \
SVJ_1500_70_0.3_peak_MC2017 \
SVJ_1500_80_0.3_peak_MC2017 \
SVJ_1500_90_0.3_peak_MC2017 \
SVJ_1700_100_0.3_peak_MC2017 \
SVJ_1700_10_0.3_peak_MC2017 \
SVJ_1700_1_0.3_peak_MC2017 \
SVJ_1700_20_0.1_peak_MC2017 \
SVJ_1700_20_0.2_peak_MC2017 \
SVJ_1700_20_0.3_high_MC2017 \
SVJ_1700_20_0.3_low_MC2017 \
SVJ_1700_20_0.3_peak_MC2017 \
SVJ_1700_20_0.4_peak_MC2017 \
SVJ_1700_20_0.5_peak_MC2017 \
SVJ_1700_20_0.6_peak_MC2017 \
SVJ_1700_20_0.7_peak_MC2017 \
SVJ_1700_20_0.8_peak_MC2017 \
SVJ_1700_20_0.9_peak_MC2017 \
SVJ_1700_20_0_peak_MC2017 \
SVJ_1700_20_1_peak_MC2017 \
SVJ_1700_30_0.3_peak_MC2017 \
SVJ_1700_40_0.3_peak_MC2017 \
SVJ_1700_50_0.3_peak_MC2017 \
SVJ_1700_5_0.3_peak_MC2017 \
SVJ_1700_60_0.3_peak_MC2017 \
SVJ_1700_70_0.3_peak_MC2017 \
SVJ_1700_80_0.3_peak_MC2017 \
SVJ_1700_90_0.3_peak_MC2017 \
SVJ_1900_100_0.3_peak_MC2017 \
SVJ_1900_10_0.3_peak_MC2017 \
SVJ_1900_1_0.3_peak_MC2017 \
SVJ_1900_20_0.1_peak_MC2017 \
SVJ_1900_20_0.2_peak_MC2017 \
SVJ_1900_20_0.3_high_MC2017 \
SVJ_1900_20_0.3_low_MC2017 \
SVJ_1900_20_0.3_peak_MC2017 \
SVJ_1900_20_0.4_peak_MC2017 \
SVJ_1900_20_0.5_peak_MC2017 \
SVJ_1900_20_0.6_peak_MC2017 \
SVJ_1900_20_0.7_peak_MC2017 \
SVJ_1900_20_0.8_peak_MC2017 \
SVJ_1900_20_0.9_peak_MC2017 \
SVJ_1900_20_0_peak_MC2017 \
SVJ_1900_20_1_peak_MC2017 \
SVJ_1900_30_0.3_peak_MC2017 \
SVJ_1900_40_0.3_peak_MC2017 \
SVJ_1900_50_0.3_peak_MC2017 \
SVJ_1900_5_0.3_peak_MC2017 \
SVJ_1900_60_0.3_peak_MC2017 \
SVJ_1900_70_0.3_peak_MC2017 \
SVJ_1900_80_0.3_peak_MC2017 \
SVJ_1900_90_0.3_peak_MC2017 \
SVJ_2100_100_0.3_peak_MC2017 \
SVJ_2100_10_0.3_peak_MC2017 \
SVJ_2100_1_0.3_peak_MC2017 \
SVJ_2100_20_0.1_peak_MC2017 \
SVJ_2100_20_0.2_peak_MC2017 \
SVJ_2100_20_0.3_high_MC2017 \
SVJ_2100_20_0.3_low_MC2017 \
SVJ_2100_20_0.3_peak_MC2017 \
SVJ_2100_20_0.4_peak_MC2017 \
SVJ_2100_20_0.5_peak_MC2017 \
SVJ_2100_20_0.6_peak_MC2017 \
SVJ_2100_20_0.7_peak_MC2017 \
SVJ_2100_20_0.8_peak_MC2017 \
SVJ_2100_20_0.9_peak_MC2017 \
SVJ_2100_20_0_peak_MC2017 \
SVJ_2100_20_1_peak_MC2017 \
SVJ_2100_30_0.3_peak_MC2017 \
SVJ_2100_40_0.3_peak_MC2017 \
SVJ_2100_50_0.3_peak_MC2017 \
SVJ_2100_5_0.3_peak_MC2017 \
SVJ_2100_60_0.3_peak_MC2017 \
SVJ_2100_70_0.3_peak_MC2017 \
SVJ_2100_80_0.3_peak_MC2017 \
SVJ_2100_90_0.3_peak_MC2017 \
SVJ_2300_100_0.3_peak_MC2017 \
SVJ_2300_10_0.3_peak_MC2017 \
SVJ_2300_1_0.3_peak_MC2017 \
SVJ_2300_20_0.1_peak_MC2017 \
SVJ_2300_20_0.2_peak_MC2017 \
SVJ_2300_20_0.3_high_MC2017 \
SVJ_2300_20_0.3_low_MC2017 \
SVJ_2300_20_0.3_peak_MC2017 \
SVJ_2300_20_0.4_peak_MC2017 \
SVJ_2300_20_0.5_peak_MC2017 \
SVJ_2300_20_0.6_peak_MC2017 \
SVJ_2300_20_0.7_peak_MC2017 \
SVJ_2300_20_0.8_peak_MC2017 \
SVJ_2300_20_0.9_peak_MC2017 \
SVJ_2300_20_0_peak_MC2017 \
SVJ_2300_20_1_peak_MC2017 \
SVJ_2300_30_0.3_peak_MC2017 \
SVJ_2300_40_0.3_peak_MC2017 \
SVJ_2300_50_0.3_peak_MC2017 \
SVJ_2300_5_0.3_peak_MC2017 \
SVJ_2300_60_0.3_peak_MC2017 \
SVJ_2300_70_0.3_peak_MC2017 \
SVJ_2300_80_0.3_peak_MC2017 \
SVJ_2300_90_0.3_peak_MC2017 \
SVJ_2500_100_0.3_peak_MC2017 \
SVJ_2500_10_0.3_peak_MC2017 \
SVJ_2500_1_0.3_peak_MC2017 \
SVJ_2500_20_0.1_peak_MC2017 \
SVJ_2500_20_0.2_peak_MC2017 \
SVJ_2500_20_0.3_high_MC2017 \
SVJ_2500_20_0.3_low_MC2017 \
SVJ_2500_20_0.3_peak_MC2017 \
SVJ_2500_20_0.4_peak_MC2017 \
SVJ_2500_20_0.5_peak_MC2017 \
SVJ_2500_20_0.6_peak_MC2017 \
SVJ_2500_20_0.7_peak_MC2017 \
SVJ_2500_20_0.8_peak_MC2017 \
SVJ_2500_20_0.9_peak_MC2017 \
SVJ_2500_20_0_peak_MC2017 \
SVJ_2500_20_1_peak_MC2017 \
SVJ_2500_30_0.3_peak_MC2017 \
SVJ_2500_40_0.3_peak_MC2017 \
SVJ_2500_50_0.3_peak_MC2017 \
SVJ_2500_5_0.3_peak_MC2017 \
SVJ_2500_60_0.3_peak_MC2017 \
SVJ_2500_70_0.3_peak_MC2017 \
SVJ_2500_80_0.3_peak_MC2017 \
SVJ_2500_90_0.3_peak_MC2017 \
SVJ_2700_100_0.3_peak_MC2017 \
SVJ_2700_10_0.3_peak_MC2017 \
SVJ_2700_1_0.3_peak_MC2017 \
SVJ_2700_20_0.1_peak_MC2017 \
SVJ_2700_20_0.2_peak_MC2017 \
SVJ_2700_20_0.3_high_MC2017 \
SVJ_2700_20_0.3_low_MC2017 \
SVJ_2700_20_0.3_peak_MC2017 \
SVJ_2700_20_0.4_peak_MC2017 \
SVJ_2700_20_0.5_peak_MC2017 \
SVJ_2700_20_0.6_peak_MC2017 \
SVJ_2700_20_0.7_peak_MC2017 \
SVJ_2700_20_0.8_peak_MC2017 \
SVJ_2700_20_0.9_peak_MC2017 \
SVJ_2700_20_0_peak_MC2017 \
SVJ_2700_20_1_peak_MC2017 \
SVJ_2700_30_0.3_peak_MC2017 \
SVJ_2700_40_0.3_peak_MC2017 \
SVJ_2700_50_0.3_peak_MC2017 \
SVJ_2700_5_0.3_peak_MC2017 \
SVJ_2700_60_0.3_peak_MC2017 \
SVJ_2700_70_0.3_peak_MC2017 \
SVJ_2700_80_0.3_peak_MC2017 \
SVJ_2700_90_0.3_peak_MC2017 \
SVJ_2900_100_0.3_peak_MC2017 \
SVJ_2900_10_0.3_peak_MC2017 \
SVJ_2900_1_0.3_peak_MC2017 \
SVJ_2900_20_0.1_peak_MC2017 \
SVJ_2900_20_0.2_peak_MC2017 \
SVJ_2900_20_0.3_high_MC2017 \
SVJ_2900_20_0.3_low_MC2017 \
SVJ_2900_20_0.3_peak_MC2017 \
SVJ_2900_20_0.4_peak_MC2017 \
SVJ_2900_20_0.5_peak_MC2017 \
SVJ_2900_20_0.6_peak_MC2017 \
SVJ_2900_20_0.7_peak_MC2017 \
SVJ_2900_20_0.8_peak_MC2017 \
SVJ_2900_20_0.9_peak_MC2017 \
SVJ_2900_20_0_peak_MC2017 \
SVJ_2900_20_1_peak_MC2017 \
SVJ_2900_30_0.3_peak_MC2017 \
SVJ_2900_40_0.3_peak_MC2017 \
SVJ_2900_50_0.3_peak_MC2017 \
SVJ_2900_5_0.3_peak_MC2017 \
SVJ_2900_60_0.3_peak_MC2017 \
SVJ_2900_70_0.3_peak_MC2017 \
SVJ_2900_80_0.3_peak_MC2017 \
SVJ_2900_90_0.3_peak_MC2017 \
SVJ_3100_100_0.3_peak_MC2017 \
SVJ_3100_10_0.3_peak_MC2017 \
SVJ_3100_1_0.3_peak_MC2017 \
SVJ_3100_20_0.1_peak_MC2017 \
SVJ_3100_20_0.2_peak_MC2017 \
SVJ_3100_20_0.3_high_MC2017 \
SVJ_3100_20_0.3_low_MC2017 \
SVJ_3100_20_0.3_peak_MC2017 \
SVJ_3100_20_0.4_peak_MC2017 \
SVJ_3100_20_0.5_peak_MC2017 \
SVJ_3100_20_0.6_peak_MC2017 \
SVJ_3100_20_0.7_peak_MC2017 \
SVJ_3100_20_0.8_peak_MC2017 \
SVJ_3100_20_0.9_peak_MC2017 \
SVJ_3100_20_0_peak_MC2017 \
SVJ_3100_20_1_peak_MC2017 \
SVJ_3100_30_0.3_peak_MC2017 \
SVJ_3100_40_0.3_peak_MC2017 \
SVJ_3100_50_0.3_peak_MC2017 \
SVJ_3100_5_0.3_peak_MC2017 \
SVJ_3100_60_0.3_peak_MC2017 \
SVJ_3100_70_0.3_peak_MC2017 \
SVJ_3100_80_0.3_peak_MC2017 \
SVJ_3100_90_0.3_peak_MC2017 \
SVJ_3300_100_0.3_peak_MC2017 \
SVJ_3300_10_0.3_peak_MC2017 \
SVJ_3300_1_0.3_peak_MC2017 \
SVJ_3300_20_0.1_peak_MC2017 \
SVJ_3300_20_0.2_peak_MC2017 \
SVJ_3300_20_0.3_high_MC2017 \
SVJ_3300_20_0.3_low_MC2017 \
SVJ_3300_20_0.3_peak_MC2017 \
SVJ_3300_20_0.4_peak_MC2017 \
SVJ_3300_20_0.5_peak_MC2017 \
SVJ_3300_20_0.6_peak_MC2017 \
SVJ_3300_20_0.7_peak_MC2017 \
SVJ_3300_20_0.8_peak_MC2017 \
SVJ_3300_20_0.9_peak_MC2017 \
SVJ_3300_20_0_peak_MC2017 \
SVJ_3300_20_1_peak_MC2017 \
SVJ_3300_30_0.3_peak_MC2017 \
SVJ_3300_40_0.3_peak_MC2017 \
SVJ_3300_50_0.3_peak_MC2017 \
SVJ_3300_5_0.3_peak_MC2017 \
SVJ_3300_60_0.3_peak_MC2017 \
SVJ_3300_70_0.3_peak_MC2017 \
SVJ_3300_80_0.3_peak_MC2017 \
SVJ_3300_90_0.3_peak_MC2017 \
SVJ_3500_100_0.3_peak_MC2017 \
SVJ_3500_10_0.3_peak_MC2017 \
SVJ_3500_1_0.3_peak_MC2017 \
SVJ_3500_20_0.1_peak_MC2017 \
SVJ_3500_20_0.2_peak_MC2017 \
SVJ_3500_20_0.3_high_MC2017 \
SVJ_3500_20_0.3_low_MC2017 \
SVJ_3500_20_0.3_peak_MC2017 \
SVJ_3500_20_0.4_peak_MC2017 \
SVJ_3500_20_0.5_peak_MC2017 \
SVJ_3500_20_0.6_peak_MC2017 \
SVJ_3500_20_0.7_peak_MC2017 \
SVJ_3500_20_0.8_peak_MC2017 \
SVJ_3500_20_0.9_peak_MC2017 \
SVJ_3500_20_0_peak_MC2017 \
SVJ_3500_20_1_peak_MC2017 \
SVJ_3500_30_0.3_peak_MC2017 \
SVJ_3500_40_0.3_peak_MC2017 \
SVJ_3500_50_0.3_peak_MC2017 \
SVJ_3500_5_0.3_peak_MC2017 \
SVJ_3500_60_0.3_peak_MC2017 \
SVJ_3500_70_0.3_peak_MC2017 \
SVJ_3500_80_0.3_peak_MC2017 \
SVJ_3500_90_0.3_peak_MC2017 \
SVJ_3700_100_0.3_peak_MC2017 \
SVJ_3700_10_0.3_peak_MC2017 \
SVJ_3700_1_0.3_peak_MC2017 \
SVJ_3700_20_0.1_peak_MC2017 \
SVJ_3700_20_0.2_peak_MC2017 \
SVJ_3700_20_0.3_high_MC2017 \
SVJ_3700_20_0.3_low_MC2017 \
SVJ_3700_20_0.3_peak_MC2017 \
SVJ_3700_20_0.4_peak_MC2017 \
SVJ_3700_20_0.5_peak_MC2017 \
SVJ_3700_20_0.6_peak_MC2017 \
SVJ_3700_20_0.7_peak_MC2017 \
SVJ_3700_20_0.8_peak_MC2017 \
SVJ_3700_20_0.9_peak_MC2017 \
SVJ_3700_20_0_peak_MC2017 \
SVJ_3700_20_1_peak_MC2017 \
SVJ_3700_30_0.3_peak_MC2017 \
SVJ_3700_40_0.3_peak_MC2017 \
SVJ_3700_50_0.3_peak_MC2017 \
SVJ_3700_5_0.3_peak_MC2017 \
SVJ_3700_60_0.3_peak_MC2017 \
SVJ_3700_70_0.3_peak_MC2017 \
SVJ_3700_80_0.3_peak_MC2017 \
SVJ_3700_90_0.3_peak_MC2017 \
SVJ_3900_100_0.3_peak_MC2017 \
SVJ_3900_10_0.3_peak_MC2017 \
SVJ_3900_1_0.3_peak_MC2017 \
SVJ_3900_20_0.1_peak_MC2017 \
SVJ_3900_20_0.2_peak_MC2017 \
SVJ_3900_20_0.3_high_MC2017 \
SVJ_3900_20_0.3_low_MC2017 \
SVJ_3900_20_0.3_peak_MC2017 \
SVJ_3900_20_0.4_peak_MC2017 \
SVJ_3900_20_0.5_peak_MC2017 \
SVJ_3900_20_0.6_peak_MC2017 \
SVJ_3900_20_0.7_peak_MC2017 \
SVJ_3900_20_0.8_peak_MC2017 \
SVJ_3900_20_0.9_peak_MC2017 \
SVJ_3900_20_0_peak_MC2017 \
SVJ_3900_20_1_peak_MC2017 \
SVJ_3900_30_0.3_peak_MC2017 \
SVJ_3900_40_0.3_peak_MC2017 \
SVJ_3900_50_0.3_peak_MC2017 \
SVJ_3900_5_0.3_peak_MC2017 \
SVJ_3900_60_0.3_peak_MC2017 \
SVJ_3900_70_0.3_peak_MC2017 \
SVJ_3900_80_0.3_peak_MC2017 \
SVJ_3900_90_0.3_peak_MC2017 \
SVJ_4100_100_0.3_peak_MC2017 \
SVJ_4100_10_0.3_peak_MC2017 \
SVJ_4100_1_0.3_peak_MC2017 \
SVJ_4100_20_0.1_peak_MC2017 \
SVJ_4100_20_0.2_peak_MC2017 \
SVJ_4100_20_0.3_high_MC2017 \
SVJ_4100_20_0.3_low_MC2017 \
SVJ_4100_20_0.3_peak_MC2017 \
SVJ_4100_20_0.4_peak_MC2017 \
SVJ_4100_20_0.5_peak_MC2017 \
SVJ_4100_20_0.6_peak_MC2017 \
SVJ_4100_20_0.7_peak_MC2017 \
SVJ_4100_20_0.8_peak_MC2017 \
SVJ_4100_20_0.9_peak_MC2017 \
SVJ_4100_20_0_peak_MC2017 \
SVJ_4100_20_1_peak_MC2017 \
SVJ_4100_30_0.3_peak_MC2017 \
SVJ_4100_40_0.3_peak_MC2017 \
SVJ_4100_50_0.3_peak_MC2017 \
SVJ_4100_5_0.3_peak_MC2017 \
SVJ_4100_60_0.3_peak_MC2017 \
SVJ_4100_70_0.3_peak_MC2017 \
SVJ_4100_80_0.3_peak_MC2017 \
SVJ_4100_90_0.3_peak_MC2017 \
SVJ_4300_100_0.3_peak_MC2017 \
SVJ_4300_10_0.3_peak_MC2017 \
SVJ_4300_1_0.3_peak_MC2017 \
SVJ_4300_20_0.1_peak_MC2017 \
SVJ_4300_20_0.2_peak_MC2017 \
SVJ_4300_20_0.3_high_MC2017 \
SVJ_4300_20_0.3_low_MC2017 \
SVJ_4300_20_0.3_peak_MC2017 \
SVJ_4300_20_0.4_peak_MC2017 \
SVJ_4300_20_0.5_peak_MC2017 \
SVJ_4300_20_0.6_peak_MC2017 \
SVJ_4300_20_0.7_peak_MC2017 \
SVJ_4300_20_0.8_peak_MC2017 \
SVJ_4300_20_0.9_peak_MC2017 \
SVJ_4300_20_0_peak_MC2017 \
SVJ_4300_20_1_peak_MC2017 \
SVJ_4300_30_0.3_peak_MC2017 \
SVJ_4300_40_0.3_peak_MC2017 \
SVJ_4300_50_0.3_peak_MC2017 \
SVJ_4300_5_0.3_peak_MC2017 \
SVJ_4300_60_0.3_peak_MC2017 \
SVJ_4300_70_0.3_peak_MC2017 \
SVJ_4300_80_0.3_peak_MC2017 \
SVJ_4300_90_0.3_peak_MC2017 \
SVJ_4500_100_0.3_peak_MC2017 \
SVJ_4500_10_0.3_peak_MC2017 \
SVJ_4500_1_0.3_peak_MC2017 \
SVJ_4500_20_0.1_peak_MC2017 \
SVJ_4500_20_0.2_peak_MC2017 \
SVJ_4500_20_0.3_high_MC2017 \
SVJ_4500_20_0.3_low_MC2017 \
SVJ_4500_20_0.3_peak_MC2017 \
SVJ_4500_20_0.4_peak_MC2017 \
SVJ_4500_20_0.5_peak_MC2017 \
SVJ_4500_20_0.6_peak_MC2017 \
SVJ_4500_20_0.7_peak_MC2017 \
SVJ_4500_20_0.8_peak_MC2017 \
SVJ_4500_20_0.9_peak_MC2017 \
SVJ_4500_20_0_peak_MC2017 \
SVJ_4500_20_1_peak_MC2017 \
SVJ_4500_30_0.3_peak_MC2017 \
SVJ_4500_40_0.3_peak_MC2017 \
SVJ_4500_50_0.3_peak_MC2017 \
SVJ_4500_5_0.3_peak_MC2017 \
SVJ_4500_60_0.3_peak_MC2017 \
SVJ_4500_70_0.3_peak_MC2017 \
SVJ_4500_80_0.3_peak_MC2017 \
SVJ_4500_90_0.3_peak_MC2017 \
SVJ_4700_100_0.3_peak_MC2017 \
SVJ_4700_10_0.3_peak_MC2017 \
SVJ_4700_1_0.3_peak_MC2017 \
SVJ_4700_20_0.1_peak_MC2017 \
SVJ_4700_20_0.2_peak_MC2017 \
SVJ_4700_20_0.3_high_MC2017 \
SVJ_4700_20_0.3_low_MC2017 \
SVJ_4700_20_0.3_peak_MC2017 \
SVJ_4700_20_0.4_peak_MC2017 \
SVJ_4700_20_0.5_peak_MC2017 \
SVJ_4700_20_0.6_peak_MC2017 \
SVJ_4700_20_0.7_peak_MC2017 \
SVJ_4700_20_0.8_peak_MC2017 \
SVJ_4700_20_0.9_peak_MC2017 \
SVJ_4700_20_0_peak_MC2017 \
SVJ_4700_20_1_peak_MC2017 \
SVJ_4700_30_0.3_peak_MC2017 \
SVJ_4700_40_0.3_peak_MC2017 \
SVJ_4700_50_0.3_peak_MC2017 \
SVJ_4700_5_0.3_peak_MC2017 \
SVJ_4700_60_0.3_peak_MC2017 \
SVJ_4700_70_0.3_peak_MC2017 \
SVJ_4700_80_0.3_peak_MC2017 \
SVJ_4700_90_0.3_peak_MC2017 \
SVJ_4900_100_0.3_peak_MC2017 \
SVJ_4900_10_0.3_peak_MC2017 \
SVJ_4900_1_0.3_peak_MC2017 \
SVJ_4900_20_0.1_peak_MC2017 \
SVJ_4900_20_0.2_peak_MC2017 \
SVJ_4900_20_0.3_high_MC2017 \
SVJ_4900_20_0.3_low_MC2017 \
SVJ_4900_20_0.3_peak_MC2017 \
SVJ_4900_20_0.4_peak_MC2017 \
SVJ_4900_20_0.5_peak_MC2017 \
SVJ_4900_20_0.6_peak_MC2017 \
SVJ_4900_20_0.7_peak_MC2017 \
SVJ_4900_20_0.8_peak_MC2017 \
SVJ_4900_20_0.9_peak_MC2017 \
SVJ_4900_20_0_peak_MC2017 \
SVJ_4900_20_1_peak_MC2017 \
SVJ_4900_30_0.3_peak_MC2017 \
SVJ_4900_40_0.3_peak_MC2017 \
SVJ_4900_50_0.3_peak_MC2017 \
SVJ_4900_5_0.3_peak_MC2017 \
SVJ_4900_60_0.3_peak_MC2017 \
SVJ_4900_70_0.3_peak_MC2017 \
SVJ_4900_80_0.3_peak_MC2017 \
SVJ_4900_90_0.3_peak_MC2017 \
SVJ_5100_100_0.3_peak_MC2017 \
SVJ_5100_10_0.3_peak_MC2017 \
SVJ_5100_1_0.3_peak_MC2017 \
SVJ_5100_20_0.1_peak_MC2017 \
SVJ_5100_20_0.2_peak_MC2017 \
SVJ_5100_20_0.3_high_MC2017 \
SVJ_5100_20_0.3_low_MC2017 \
SVJ_5100_20_0.3_peak_MC2017 \
SVJ_5100_20_0.4_peak_MC2017 \
SVJ_5100_20_0.5_peak_MC2017 \
SVJ_5100_20_0.6_peak_MC2017 \
SVJ_5100_20_0.7_peak_MC2017 \
SVJ_5100_20_0.8_peak_MC2017 \
SVJ_5100_20_0.9_peak_MC2017 \
SVJ_5100_20_0_peak_MC2017 \
SVJ_5100_20_1_peak_MC2017 \
SVJ_5100_30_0.3_peak_MC2017 \
SVJ_5100_40_0.3_peak_MC2017 \
SVJ_5100_50_0.3_peak_MC2017 \
SVJ_5100_5_0.3_peak_MC2017 \
SVJ_5100_60_0.3_peak_MC2017 \
SVJ_5100_70_0.3_peak_MC2017 \
SVJ_5100_80_0.3_peak_MC2017 \
SVJ_5100_90_0.3_peak_MC2017 \
)
