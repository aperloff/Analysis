#!/bin/bash

export SAMPLES=(
T1tttt_1000_100_MC2017_fast \
T1tttt_1000_1_MC2017_fast \
T1tttt_1000_200_MC2017_fast \
T1tttt_1000_300_MC2017_fast \
T1tttt_1000_350_MC2017_fast \
T1tttt_1000_400_MC2017_fast \
T1tttt_1000_450_MC2017_fast \
T1tttt_1000_500_MC2017_fast \
T1tttt_1000_550_MC2017_fast \
T1tttt_1000_600_MC2017_fast \
T1tttt_1000_650_MC2017_fast \
T1tttt_1000_700_MC2017_fast \
T1tttt_1000_750_MC2017_fast \
T1tttt_1000_775_MC2017_fast \
T1tttt_1050_300_MC2017_fast \
T1tttt_1050_350_MC2017_fast \
T1tttt_1050_400_MC2017_fast \
T1tttt_1050_450_MC2017_fast \
T1tttt_1050_500_MC2017_fast \
T1tttt_1050_550_MC2017_fast \
T1tttt_1050_600_MC2017_fast \
T1tttt_1050_650_MC2017_fast \
T1tttt_1050_700_MC2017_fast \
T1tttt_1050_750_MC2017_fast \
T1tttt_1050_800_MC2017_fast \
T1tttt_1050_825_MC2017_fast \
T1tttt_1100_100_MC2017_fast \
T1tttt_1100_1_MC2017_fast \
T1tttt_1100_200_MC2017_fast \
T1tttt_1100_300_MC2017_fast \
T1tttt_1100_350_MC2017_fast \
T1tttt_1100_400_MC2017_fast \
T1tttt_1100_450_MC2017_fast \
T1tttt_1100_500_MC2017_fast \
T1tttt_1100_550_MC2017_fast \
T1tttt_1100_600_MC2017_fast \
T1tttt_1100_650_MC2017_fast \
T1tttt_1100_700_MC2017_fast \
T1tttt_1100_750_MC2017_fast \
T1tttt_1100_800_MC2017_fast \
T1tttt_1100_850_MC2017_fast \
T1tttt_1100_875_MC2017_fast \
T1tttt_1150_300_MC2017_fast \
T1tttt_1150_350_MC2017_fast \
T1tttt_1150_400_MC2017_fast \
T1tttt_1150_450_MC2017_fast \
T1tttt_1150_500_MC2017_fast \
T1tttt_1150_550_MC2017_fast \
T1tttt_1150_600_MC2017_fast \
T1tttt_1150_650_MC2017_fast \
T1tttt_1150_700_MC2017_fast \
T1tttt_1150_750_MC2017_fast \
T1tttt_1150_800_MC2017_fast \
T1tttt_1150_850_MC2017_fast \
T1tttt_1150_900_MC2017_fast \
T1tttt_1150_925_MC2017_fast \
T1tttt_1200_100_MC2017_fast \
T1tttt_1200_1_MC2017_fast \
T1tttt_1200_200_MC2017_fast \
T1tttt_1200_300_MC2017_fast \
T1tttt_1200_350_MC2017_fast \
T1tttt_1200_400_MC2017_fast \
T1tttt_1200_450_MC2017_fast \
T1tttt_1200_500_MC2017_fast \
T1tttt_1200_550_MC2017_fast \
T1tttt_1200_600_MC2017_fast \
T1tttt_1200_650_MC2017_fast \
T1tttt_1200_700_MC2017_fast \
T1tttt_1200_750_MC2017_fast \
T1tttt_1200_800_MC2017_fast \
T1tttt_1200_850_MC2017_fast \
T1tttt_1200_900_MC2017_fast \
T1tttt_1200_950_MC2017_fast \
T1tttt_1200_975_MC2017_fast \
T1tttt_1250_1000_MC2017_fast \
T1tttt_1250_100_MC2017_fast \
T1tttt_1250_1025_MC2017_fast \
T1tttt_1250_1_MC2017_fast \
T1tttt_1250_200_MC2017_fast \
T1tttt_1250_300_MC2017_fast \
T1tttt_1250_350_MC2017_fast \
T1tttt_1250_400_MC2017_fast \
T1tttt_1250_450_MC2017_fast \
T1tttt_1250_500_MC2017_fast \
T1tttt_1250_550_MC2017_fast \
T1tttt_1250_600_MC2017_fast \
T1tttt_1250_650_MC2017_fast \
T1tttt_1250_700_MC2017_fast \
T1tttt_1250_750_MC2017_fast \
T1tttt_1250_800_MC2017_fast \
T1tttt_1250_850_MC2017_fast \
T1tttt_1250_900_MC2017_fast \
T1tttt_1250_950_MC2017_fast \
T1tttt_1300_1000_MC2017_fast \
T1tttt_1300_100_MC2017_fast \
T1tttt_1300_1050_MC2017_fast \
T1tttt_1300_1075_MC2017_fast \
T1tttt_1300_1_MC2017_fast \
T1tttt_1300_200_MC2017_fast \
T1tttt_1300_300_MC2017_fast \
T1tttt_1300_350_MC2017_fast \
T1tttt_1300_400_MC2017_fast \
T1tttt_1300_450_MC2017_fast \
T1tttt_1300_500_MC2017_fast \
T1tttt_1300_550_MC2017_fast \
T1tttt_1300_600_MC2017_fast \
T1tttt_1300_650_MC2017_fast \
T1tttt_1300_700_MC2017_fast \
T1tttt_1300_750_MC2017_fast \
T1tttt_1300_800_MC2017_fast \
T1tttt_1300_850_MC2017_fast \
T1tttt_1300_900_MC2017_fast \
T1tttt_1300_950_MC2017_fast \
T1tttt_1350_1000_MC2017_fast \
T1tttt_1350_100_MC2017_fast \
T1tttt_1350_1050_MC2017_fast \
T1tttt_1350_1100_MC2017_fast \
T1tttt_1350_1125_MC2017_fast \
T1tttt_1350_1_MC2017_fast \
T1tttt_1350_200_MC2017_fast \
T1tttt_1350_300_MC2017_fast \
T1tttt_1350_350_MC2017_fast \
T1tttt_1350_400_MC2017_fast \
T1tttt_1350_450_MC2017_fast \
T1tttt_1350_500_MC2017_fast \
T1tttt_1350_550_MC2017_fast \
T1tttt_1350_600_MC2017_fast \
T1tttt_1350_650_MC2017_fast \
T1tttt_1350_700_MC2017_fast \
T1tttt_1350_750_MC2017_fast \
T1tttt_1350_800_MC2017_fast \
T1tttt_1350_850_MC2017_fast \
T1tttt_1350_900_MC2017_fast \
T1tttt_1350_950_MC2017_fast \
T1tttt_1400_1000_MC2017_fast \
T1tttt_1400_100_MC2017_fast \
T1tttt_1400_1050_MC2017_fast \
T1tttt_1400_1100_MC2017_fast \
T1tttt_1400_1150_MC2017_fast \
T1tttt_1400_1175_MC2017_fast \
T1tttt_1400_1_MC2017_fast \
T1tttt_1400_200_MC2017_fast \
T1tttt_1400_300_MC2017_fast \
T1tttt_1400_400_MC2017_fast \
T1tttt_1400_450_MC2017_fast \
T1tttt_1400_500_MC2017_fast \
T1tttt_1400_550_MC2017_fast \
T1tttt_1400_600_MC2017_fast \
T1tttt_1400_650_MC2017_fast \
T1tttt_1400_700_MC2017_fast \
T1tttt_1400_750_MC2017_fast \
T1tttt_1400_800_MC2017_fast \
T1tttt_1400_850_MC2017_fast \
T1tttt_1400_900_MC2017_fast \
T1tttt_1400_950_MC2017_fast \
T1tttt_1450_1000_MC2017_fast \
T1tttt_1450_100_MC2017_fast \
T1tttt_1450_1050_MC2017_fast \
T1tttt_1450_1100_MC2017_fast \
T1tttt_1450_1150_MC2017_fast \
T1tttt_1450_1200_MC2017_fast \
T1tttt_1450_1225_MC2017_fast \
T1tttt_1450_1_MC2017_fast \
T1tttt_1450_200_MC2017_fast \
T1tttt_1450_300_MC2017_fast \
T1tttt_1450_400_MC2017_fast \
T1tttt_1450_450_MC2017_fast \
T1tttt_1450_500_MC2017_fast \
T1tttt_1450_550_MC2017_fast \
T1tttt_1450_600_MC2017_fast \
T1tttt_1450_650_MC2017_fast \
T1tttt_1450_700_MC2017_fast \
T1tttt_1450_750_MC2017_fast \
T1tttt_1450_800_MC2017_fast \
T1tttt_1450_850_MC2017_fast \
T1tttt_1450_900_MC2017_fast \
T1tttt_1450_950_MC2017_fast \
T1tttt_1500_1000_MC2017_fast \
T1tttt_1500_100_MC2017_fast \
T1tttt_1500_1050_MC2017_fast \
T1tttt_1500_1100_MC2017_fast \
T1tttt_1500_1150_MC2017_fast \
T1tttt_1500_1200_MC2017_fast \
T1tttt_1500_1250_MC2017_fast \
T1tttt_1500_1275_MC2017_fast \
T1tttt_1500_1_MC2017_fast \
T1tttt_1500_200_MC2017_fast \
T1tttt_1500_300_MC2017_fast \
T1tttt_1500_400_MC2017_fast \
T1tttt_1500_500_MC2017_fast \
T1tttt_1500_550_MC2017_fast \
T1tttt_1500_600_MC2017_fast \
T1tttt_1500_650_MC2017_fast \
T1tttt_1500_700_MC2017_fast \
T1tttt_1500_750_MC2017_fast \
T1tttt_1500_800_MC2017_fast \
T1tttt_1500_850_MC2017_fast \
T1tttt_1500_900_MC2017_fast \
T1tttt_1500_950_MC2017_fast \
T1tttt_1550_1000_MC2017_fast \
T1tttt_1550_100_MC2017_fast \
T1tttt_1550_1050_MC2017_fast \
T1tttt_1550_1100_MC2017_fast \
T1tttt_1550_1150_MC2017_fast \
T1tttt_1550_1200_MC2017_fast \
T1tttt_1550_1250_MC2017_fast \
T1tttt_1550_1300_MC2017_fast \
T1tttt_1550_1325_MC2017_fast \
T1tttt_1550_1_MC2017_fast \
T1tttt_1550_200_MC2017_fast \
T1tttt_1550_300_MC2017_fast \
T1tttt_1550_400_MC2017_fast \
T1tttt_1550_500_MC2017_fast \
T1tttt_1550_550_MC2017_fast \
T1tttt_1550_600_MC2017_fast \
T1tttt_1550_650_MC2017_fast \
T1tttt_1550_700_MC2017_fast \
T1tttt_1550_750_MC2017_fast \
T1tttt_1550_800_MC2017_fast \
T1tttt_1550_850_MC2017_fast \
T1tttt_1550_900_MC2017_fast \
T1tttt_1550_950_MC2017_fast \
T1tttt_1600_1000_MC2017_fast \
T1tttt_1600_100_MC2017_fast \
T1tttt_1600_1050_MC2017_fast \
T1tttt_1600_1100_MC2017_fast \
T1tttt_1600_1150_MC2017_fast \
T1tttt_1600_1200_MC2017_fast \
T1tttt_1600_1250_MC2017_fast \
T1tttt_1600_1300_MC2017_fast \
T1tttt_1600_1350_MC2017_fast \
T1tttt_1600_1375_MC2017_fast \
T1tttt_1600_1_MC2017_fast \
T1tttt_1600_200_MC2017_fast \
T1tttt_1600_300_MC2017_fast \
T1tttt_1600_400_MC2017_fast \
T1tttt_1600_500_MC2017_fast \
T1tttt_1600_600_MC2017_fast \
T1tttt_1600_650_MC2017_fast \
T1tttt_1600_700_MC2017_fast \
T1tttt_1600_750_MC2017_fast \
T1tttt_1600_800_MC2017_fast \
T1tttt_1600_850_MC2017_fast \
T1tttt_1600_900_MC2017_fast \
T1tttt_1600_950_MC2017_fast \
T1tttt_1650_1000_MC2017_fast \
T1tttt_1650_100_MC2017_fast \
T1tttt_1650_1050_MC2017_fast \
T1tttt_1650_1100_MC2017_fast \
T1tttt_1650_1150_MC2017_fast \
T1tttt_1650_1200_MC2017_fast \
T1tttt_1650_1250_MC2017_fast \
T1tttt_1650_1300_MC2017_fast \
T1tttt_1650_1350_MC2017_fast \
T1tttt_1650_1400_MC2017_fast \
T1tttt_1650_1425_MC2017_fast \
T1tttt_1650_1_MC2017_fast \
T1tttt_1650_200_MC2017_fast \
T1tttt_1650_300_MC2017_fast \
T1tttt_1650_400_MC2017_fast \
T1tttt_1650_500_MC2017_fast \
T1tttt_1650_600_MC2017_fast \
T1tttt_1650_650_MC2017_fast \
T1tttt_1650_700_MC2017_fast \
T1tttt_1650_750_MC2017_fast \
T1tttt_1650_800_MC2017_fast \
T1tttt_1650_850_MC2017_fast \
T1tttt_1650_900_MC2017_fast \
T1tttt_1650_950_MC2017_fast \
T1tttt_1700_1000_MC2017_fast \
T1tttt_1700_100_MC2017_fast \
T1tttt_1700_1050_MC2017_fast \
T1tttt_1700_1100_MC2017_fast \
T1tttt_1700_1150_MC2017_fast \
T1tttt_1700_1200_MC2017_fast \
T1tttt_1700_1250_MC2017_fast \
T1tttt_1700_1300_MC2017_fast \
T1tttt_1700_1350_MC2017_fast \
T1tttt_1700_1400_MC2017_fast \
T1tttt_1700_1450_MC2017_fast \
T1tttt_1700_1475_MC2017_fast \
T1tttt_1700_1_MC2017_fast \
T1tttt_1700_200_MC2017_fast \
T1tttt_1700_300_MC2017_fast \
T1tttt_1700_400_MC2017_fast \
T1tttt_1700_500_MC2017_fast \
T1tttt_1700_600_MC2017_fast \
T1tttt_1700_700_MC2017_fast \
T1tttt_1700_750_MC2017_fast \
T1tttt_1700_800_MC2017_fast \
T1tttt_1700_850_MC2017_fast \
T1tttt_1700_900_MC2017_fast \
T1tttt_1700_950_MC2017_fast \
T1tttt_1750_1000_MC2017_fast \
T1tttt_1750_100_MC2017_fast \
T1tttt_1750_1050_MC2017_fast \
T1tttt_1750_1100_MC2017_fast \
T1tttt_1750_1150_MC2017_fast \
T1tttt_1750_1200_MC2017_fast \
T1tttt_1750_1250_MC2017_fast \
T1tttt_1750_1300_MC2017_fast \
T1tttt_1750_1350_MC2017_fast \
T1tttt_1750_1400_MC2017_fast \
T1tttt_1750_1450_MC2017_fast \
T1tttt_1750_1500_MC2017_fast \
T1tttt_1750_1525_MC2017_fast \
T1tttt_1750_1_MC2017_fast \
T1tttt_1750_200_MC2017_fast \
T1tttt_1750_300_MC2017_fast \
T1tttt_1750_400_MC2017_fast \
T1tttt_1750_500_MC2017_fast \
T1tttt_1750_600_MC2017_fast \
T1tttt_1750_700_MC2017_fast \
T1tttt_1750_750_MC2017_fast \
T1tttt_1750_800_MC2017_fast \
T1tttt_1750_850_MC2017_fast \
T1tttt_1750_900_MC2017_fast \
T1tttt_1750_950_MC2017_fast \
T1tttt_1800_1000_MC2017_fast \
T1tttt_1800_100_MC2017_fast \
T1tttt_1800_1050_MC2017_fast \
T1tttt_1800_1100_MC2017_fast \
T1tttt_1800_1150_MC2017_fast \
T1tttt_1800_1200_MC2017_fast \
T1tttt_1800_1250_MC2017_fast \
T1tttt_1800_1300_MC2017_fast \
T1tttt_1800_1350_MC2017_fast \
T1tttt_1800_1400_MC2017_fast \
T1tttt_1800_1450_MC2017_fast \
T1tttt_1800_1500_MC2017_fast \
T1tttt_1800_1550_MC2017_fast \
T1tttt_1800_1575_MC2017_fast \
T1tttt_1800_1_MC2017_fast \
T1tttt_1800_200_MC2017_fast \
T1tttt_1800_300_MC2017_fast \
T1tttt_1800_400_MC2017_fast \
T1tttt_1800_500_MC2017_fast \
T1tttt_1800_600_MC2017_fast \
T1tttt_1800_700_MC2017_fast \
T1tttt_1800_800_MC2017_fast \
T1tttt_1800_850_MC2017_fast \
T1tttt_1800_900_MC2017_fast \
T1tttt_1800_950_MC2017_fast \
T1tttt_1850_1000_MC2017_fast \
T1tttt_1850_100_MC2017_fast \
T1tttt_1850_1050_MC2017_fast \
T1tttt_1850_1100_MC2017_fast \
T1tttt_1850_1150_MC2017_fast \
T1tttt_1850_1200_MC2017_fast \
T1tttt_1850_1250_MC2017_fast \
T1tttt_1850_1300_MC2017_fast \
T1tttt_1850_1350_MC2017_fast \
T1tttt_1850_1400_MC2017_fast \
T1tttt_1850_1450_MC2017_fast \
T1tttt_1850_1500_MC2017_fast \
T1tttt_1850_1550_MC2017_fast \
T1tttt_1850_1600_MC2017_fast \
T1tttt_1850_1_MC2017_fast \
T1tttt_1850_200_MC2017_fast \
T1tttt_1850_300_MC2017_fast \
T1tttt_1850_400_MC2017_fast \
T1tttt_1850_500_MC2017_fast \
T1tttt_1850_600_MC2017_fast \
T1tttt_1850_700_MC2017_fast \
T1tttt_1850_800_MC2017_fast \
T1tttt_1850_850_MC2017_fast \
T1tttt_1850_900_MC2017_fast \
T1tttt_1850_950_MC2017_fast \
T1tttt_1900_1000_MC2017_fast \
T1tttt_1900_100_MC2017_fast \
T1tttt_1900_1050_MC2017_fast \
T1tttt_1900_1100_MC2017_fast \
T1tttt_1900_1150_MC2017_fast \
T1tttt_1900_1200_MC2017_fast \
T1tttt_1900_1250_MC2017_fast \
T1tttt_1900_1300_MC2017_fast \
T1tttt_1900_1350_MC2017_fast \
T1tttt_1900_1400_MC2017_fast \
T1tttt_1900_1450_MC2017_fast \
T1tttt_1900_1500_MC2017_fast \
T1tttt_1900_1550_MC2017_fast \
T1tttt_1900_1600_MC2017_fast \
T1tttt_1900_1_MC2017_fast \
T1tttt_1900_200_MC2017_fast \
T1tttt_1900_300_MC2017_fast \
T1tttt_1900_400_MC2017_fast \
T1tttt_1900_500_MC2017_fast \
T1tttt_1900_600_MC2017_fast \
T1tttt_1900_700_MC2017_fast \
T1tttt_1900_800_MC2017_fast \
T1tttt_1900_900_MC2017_fast \
T1tttt_1900_950_MC2017_fast \
T1tttt_1950_1000_MC2017_fast \
T1tttt_1950_100_MC2017_fast \
T1tttt_1950_1050_MC2017_fast \
T1tttt_1950_1100_MC2017_fast \
T1tttt_1950_1150_MC2017_fast \
T1tttt_1950_1200_MC2017_fast \
T1tttt_1950_1250_MC2017_fast \
T1tttt_1950_1300_MC2017_fast \
T1tttt_1950_1350_MC2017_fast \
T1tttt_1950_1400_MC2017_fast \
T1tttt_1950_1450_MC2017_fast \
T1tttt_1950_1500_MC2017_fast \
T1tttt_1950_1550_MC2017_fast \
T1tttt_1950_1600_MC2017_fast \
T1tttt_1950_1_MC2017_fast \
T1tttt_1950_200_MC2017_fast \
T1tttt_1950_300_MC2017_fast \
T1tttt_1950_400_MC2017_fast \
T1tttt_1950_500_MC2017_fast \
T1tttt_1950_600_MC2017_fast \
T1tttt_1950_700_MC2017_fast \
T1tttt_1950_800_MC2017_fast \
T1tttt_1950_900_MC2017_fast \
T1tttt_1950_950_MC2017_fast \
T1tttt_2000_1000_MC2017_fast \
T1tttt_2000_100_MC2017_fast \
T1tttt_2000_1050_MC2017_fast \
T1tttt_2000_1100_MC2017_fast \
T1tttt_2000_1150_MC2017_fast \
T1tttt_2000_1200_MC2017_fast \
T1tttt_2000_1250_MC2017_fast \
T1tttt_2000_1300_MC2017_fast \
T1tttt_2000_1350_MC2017_fast \
T1tttt_2000_1400_MC2017_fast \
T1tttt_2000_1450_MC2017_fast \
T1tttt_2000_1500_MC2017_fast \
T1tttt_2000_1550_MC2017_fast \
T1tttt_2000_1600_MC2017_fast \
T1tttt_2000_1_MC2017_fast \
T1tttt_2000_200_MC2017_fast \
T1tttt_2000_300_MC2017_fast \
T1tttt_2000_400_MC2017_fast \
T1tttt_2000_500_MC2017_fast \
T1tttt_2000_600_MC2017_fast \
T1tttt_2000_700_MC2017_fast \
T1tttt_2000_800_MC2017_fast \
T1tttt_2000_900_MC2017_fast \
T1tttt_2050_1000_MC2017_fast \
T1tttt_2050_100_MC2017_fast \
T1tttt_2050_1050_MC2017_fast \
T1tttt_2050_1100_MC2017_fast \
T1tttt_2050_1150_MC2017_fast \
T1tttt_2050_1200_MC2017_fast \
T1tttt_2050_1250_MC2017_fast \
T1tttt_2050_1300_MC2017_fast \
T1tttt_2050_1350_MC2017_fast \
T1tttt_2050_1400_MC2017_fast \
T1tttt_2050_1450_MC2017_fast \
T1tttt_2050_1500_MC2017_fast \
T1tttt_2050_1550_MC2017_fast \
T1tttt_2050_1600_MC2017_fast \
T1tttt_2050_1_MC2017_fast \
T1tttt_2050_200_MC2017_fast \
T1tttt_2050_300_MC2017_fast \
T1tttt_2050_400_MC2017_fast \
T1tttt_2050_500_MC2017_fast \
T1tttt_2050_600_MC2017_fast \
T1tttt_2050_700_MC2017_fast \
T1tttt_2050_800_MC2017_fast \
T1tttt_2050_900_MC2017_fast \
T1tttt_2100_1000_MC2017_fast \
T1tttt_2100_100_MC2017_fast \
T1tttt_2100_1100_MC2017_fast \
T1tttt_2100_1150_MC2017_fast \
T1tttt_2100_1200_MC2017_fast \
T1tttt_2100_1250_MC2017_fast \
T1tttt_2100_1300_MC2017_fast \
T1tttt_2100_1350_MC2017_fast \
T1tttt_2100_1400_MC2017_fast \
T1tttt_2100_1450_MC2017_fast \
T1tttt_2100_1500_MC2017_fast \
T1tttt_2100_1550_MC2017_fast \
T1tttt_2100_1600_MC2017_fast \
T1tttt_2100_1_MC2017_fast \
T1tttt_2100_200_MC2017_fast \
T1tttt_2100_300_MC2017_fast \
T1tttt_2100_400_MC2017_fast \
T1tttt_2100_500_MC2017_fast \
T1tttt_2100_600_MC2017_fast \
T1tttt_2100_700_MC2017_fast \
T1tttt_2100_800_MC2017_fast \
T1tttt_2100_900_MC2017_fast \
T1tttt_2150_1000_MC2017_fast \
T1tttt_2150_100_MC2017_fast \
T1tttt_2150_1100_MC2017_fast \
T1tttt_2150_1150_MC2017_fast \
T1tttt_2150_1200_MC2017_fast \
T1tttt_2150_1250_MC2017_fast \
T1tttt_2150_1300_MC2017_fast \
T1tttt_2150_1350_MC2017_fast \
T1tttt_2150_1400_MC2017_fast \
T1tttt_2150_1450_MC2017_fast \
T1tttt_2150_1500_MC2017_fast \
T1tttt_2150_1550_MC2017_fast \
T1tttt_2150_1600_MC2017_fast \
T1tttt_2150_1_MC2017_fast \
T1tttt_2150_200_MC2017_fast \
T1tttt_2150_300_MC2017_fast \
T1tttt_2150_400_MC2017_fast \
T1tttt_2150_500_MC2017_fast \
T1tttt_2150_600_MC2017_fast \
T1tttt_2150_700_MC2017_fast \
T1tttt_2150_800_MC2017_fast \
T1tttt_2150_900_MC2017_fast \
T1tttt_2200_1000_MC2017_fast \
T1tttt_2200_100_MC2017_fast \
T1tttt_2200_1100_MC2017_fast \
T1tttt_2200_1200_MC2017_fast \
T1tttt_2200_1250_MC2017_fast \
T1tttt_2200_1300_MC2017_fast \
T1tttt_2200_1350_MC2017_fast \
T1tttt_2200_1400_MC2017_fast \
T1tttt_2200_1450_MC2017_fast \
T1tttt_2200_1500_MC2017_fast \
T1tttt_2200_1550_MC2017_fast \
T1tttt_2200_1600_MC2017_fast \
T1tttt_2200_1_MC2017_fast \
T1tttt_2200_200_MC2017_fast \
T1tttt_2200_300_MC2017_fast \
T1tttt_2200_400_MC2017_fast \
T1tttt_2200_500_MC2017_fast \
T1tttt_2200_600_MC2017_fast \
T1tttt_2200_700_MC2017_fast \
T1tttt_2200_800_MC2017_fast \
T1tttt_2200_900_MC2017_fast \
T1tttt_2250_1000_MC2017_fast \
T1tttt_2250_100_MC2017_fast \
T1tttt_2250_1100_MC2017_fast \
T1tttt_2250_1200_MC2017_fast \
T1tttt_2250_1250_MC2017_fast \
T1tttt_2250_1300_MC2017_fast \
T1tttt_2250_1350_MC2017_fast \
T1tttt_2250_1400_MC2017_fast \
T1tttt_2250_1450_MC2017_fast \
T1tttt_2250_1500_MC2017_fast \
T1tttt_2250_1550_MC2017_fast \
T1tttt_2250_1600_MC2017_fast \
T1tttt_2250_1_MC2017_fast \
T1tttt_2250_200_MC2017_fast \
T1tttt_2250_300_MC2017_fast \
T1tttt_2250_400_MC2017_fast \
T1tttt_2250_500_MC2017_fast \
T1tttt_2250_600_MC2017_fast \
T1tttt_2250_700_MC2017_fast \
T1tttt_2250_800_MC2017_fast \
T1tttt_2250_900_MC2017_fast \
T1tttt_2300_1000_MC2017_fast \
T1tttt_2300_100_MC2017_fast \
T1tttt_2300_1100_MC2017_fast \
T1tttt_2300_1200_MC2017_fast \
T1tttt_2300_1300_MC2017_fast \
T1tttt_2300_1350_MC2017_fast \
T1tttt_2300_1400_MC2017_fast \
T1tttt_2300_1450_MC2017_fast \
T1tttt_2300_1500_MC2017_fast \
T1tttt_2300_1550_MC2017_fast \
T1tttt_2300_1600_MC2017_fast \
T1tttt_2300_1_MC2017_fast \
T1tttt_2300_200_MC2017_fast \
T1tttt_2300_300_MC2017_fast \
T1tttt_2300_400_MC2017_fast \
T1tttt_2300_500_MC2017_fast \
T1tttt_2300_600_MC2017_fast \
T1tttt_2300_700_MC2017_fast \
T1tttt_2300_800_MC2017_fast \
T1tttt_2300_900_MC2017_fast \
T1tttt_2350_1000_MC2017_fast \
T1tttt_2350_100_MC2017_fast \
T1tttt_2350_1100_MC2017_fast \
T1tttt_2350_1200_MC2017_fast \
T1tttt_2350_1300_MC2017_fast \
T1tttt_2350_1350_MC2017_fast \
T1tttt_2350_1400_MC2017_fast \
T1tttt_2350_1450_MC2017_fast \
T1tttt_2350_1500_MC2017_fast \
T1tttt_2350_1550_MC2017_fast \
T1tttt_2350_1600_MC2017_fast \
T1tttt_2350_1_MC2017_fast \
T1tttt_2350_200_MC2017_fast \
T1tttt_2350_300_MC2017_fast \
T1tttt_2350_400_MC2017_fast \
T1tttt_2350_500_MC2017_fast \
T1tttt_2350_600_MC2017_fast \
T1tttt_2350_700_MC2017_fast \
T1tttt_2350_800_MC2017_fast \
T1tttt_2350_900_MC2017_fast \
T1tttt_2400_1000_MC2017_fast \
T1tttt_2400_100_MC2017_fast \
T1tttt_2400_1100_MC2017_fast \
T1tttt_2400_1200_MC2017_fast \
T1tttt_2400_1300_MC2017_fast \
T1tttt_2400_1400_MC2017_fast \
T1tttt_2400_1450_MC2017_fast \
T1tttt_2400_1500_MC2017_fast \
T1tttt_2400_1550_MC2017_fast \
T1tttt_2400_1600_MC2017_fast \
T1tttt_2400_1_MC2017_fast \
T1tttt_2400_200_MC2017_fast \
T1tttt_2400_300_MC2017_fast \
T1tttt_2400_400_MC2017_fast \
T1tttt_2400_500_MC2017_fast \
T1tttt_2400_600_MC2017_fast \
T1tttt_2400_700_MC2017_fast \
T1tttt_2400_800_MC2017_fast \
T1tttt_2400_900_MC2017_fast \
T1tttt_2450_1000_MC2017_fast \
T1tttt_2450_100_MC2017_fast \
T1tttt_2450_1100_MC2017_fast \
T1tttt_2450_1200_MC2017_fast \
T1tttt_2450_1300_MC2017_fast \
T1tttt_2450_1400_MC2017_fast \
T1tttt_2450_1450_MC2017_fast \
T1tttt_2450_1500_MC2017_fast \
T1tttt_2450_1550_MC2017_fast \
T1tttt_2450_1600_MC2017_fast \
T1tttt_2450_1_MC2017_fast \
T1tttt_2450_200_MC2017_fast \
T1tttt_2450_300_MC2017_fast \
T1tttt_2450_400_MC2017_fast \
T1tttt_2450_500_MC2017_fast \
T1tttt_2450_600_MC2017_fast \
T1tttt_2450_700_MC2017_fast \
T1tttt_2450_800_MC2017_fast \
T1tttt_2450_900_MC2017_fast \
T1tttt_2500_1000_MC2017_fast \
T1tttt_2500_100_MC2017_fast \
T1tttt_2500_1100_MC2017_fast \
T1tttt_2500_1200_MC2017_fast \
T1tttt_2500_1300_MC2017_fast \
T1tttt_2500_1400_MC2017_fast \
T1tttt_2500_1500_MC2017_fast \
T1tttt_2500_1550_MC2017_fast \
T1tttt_2500_1600_MC2017_fast \
T1tttt_2500_1_MC2017_fast \
T1tttt_2500_200_MC2017_fast \
T1tttt_2500_300_MC2017_fast \
T1tttt_2500_400_MC2017_fast \
T1tttt_2500_500_MC2017_fast \
T1tttt_2500_600_MC2017_fast \
T1tttt_2500_700_MC2017_fast \
T1tttt_2500_800_MC2017_fast \
T1tttt_2500_900_MC2017_fast \
T1tttt_2550_1000_MC2017_fast \
T1tttt_2550_100_MC2017_fast \
T1tttt_2550_1100_MC2017_fast \
T1tttt_2550_1200_MC2017_fast \
T1tttt_2550_1300_MC2017_fast \
T1tttt_2550_1400_MC2017_fast \
T1tttt_2550_1500_MC2017_fast \
T1tttt_2550_1550_MC2017_fast \
T1tttt_2550_1600_MC2017_fast \
T1tttt_2550_1_MC2017_fast \
T1tttt_2550_200_MC2017_fast \
T1tttt_2550_300_MC2017_fast \
T1tttt_2550_400_MC2017_fast \
T1tttt_2550_500_MC2017_fast \
T1tttt_2550_600_MC2017_fast \
T1tttt_2550_700_MC2017_fast \
T1tttt_2550_800_MC2017_fast \
T1tttt_2550_900_MC2017_fast \
T1tttt_2600_1000_MC2017_fast \
T1tttt_2600_100_MC2017_fast \
T1tttt_2600_1100_MC2017_fast \
T1tttt_2600_1200_MC2017_fast \
T1tttt_2600_1300_MC2017_fast \
T1tttt_2600_1400_MC2017_fast \
T1tttt_2600_1500_MC2017_fast \
T1tttt_2600_1600_MC2017_fast \
T1tttt_2600_1_MC2017_fast \
T1tttt_2600_200_MC2017_fast \
T1tttt_2600_300_MC2017_fast \
T1tttt_2600_400_MC2017_fast \
T1tttt_2600_500_MC2017_fast \
T1tttt_2600_600_MC2017_fast \
T1tttt_2600_700_MC2017_fast \
T1tttt_2600_800_MC2017_fast \
T1tttt_2600_900_MC2017_fast \
T1tttt_2650_1000_MC2017_fast \
T1tttt_2650_100_MC2017_fast \
T1tttt_2650_1100_MC2017_fast \
T1tttt_2650_1200_MC2017_fast \
T1tttt_2650_1300_MC2017_fast \
T1tttt_2650_1400_MC2017_fast \
T1tttt_2650_1500_MC2017_fast \
T1tttt_2650_1600_MC2017_fast \
T1tttt_2650_1_MC2017_fast \
T1tttt_2650_200_MC2017_fast \
T1tttt_2650_300_MC2017_fast \
T1tttt_2650_400_MC2017_fast \
T1tttt_2650_500_MC2017_fast \
T1tttt_2650_600_MC2017_fast \
T1tttt_2650_700_MC2017_fast \
T1tttt_2650_800_MC2017_fast \
T1tttt_2650_900_MC2017_fast \
T1tttt_2700_1000_MC2017_fast \
T1tttt_2700_100_MC2017_fast \
T1tttt_2700_1100_MC2017_fast \
T1tttt_2700_1200_MC2017_fast \
T1tttt_2700_1300_MC2017_fast \
T1tttt_2700_1400_MC2017_fast \
T1tttt_2700_1500_MC2017_fast \
T1tttt_2700_1600_MC2017_fast \
T1tttt_2700_1_MC2017_fast \
T1tttt_2700_200_MC2017_fast \
T1tttt_2700_300_MC2017_fast \
T1tttt_2700_400_MC2017_fast \
T1tttt_2700_500_MC2017_fast \
T1tttt_2700_600_MC2017_fast \
T1tttt_2700_700_MC2017_fast \
T1tttt_2700_800_MC2017_fast \
T1tttt_2700_900_MC2017_fast \
T1tttt_2750_1000_MC2017_fast \
T1tttt_2750_100_MC2017_fast \
T1tttt_2750_1100_MC2017_fast \
T1tttt_2750_1200_MC2017_fast \
T1tttt_2750_1300_MC2017_fast \
T1tttt_2750_1400_MC2017_fast \
T1tttt_2750_1500_MC2017_fast \
T1tttt_2750_1600_MC2017_fast \
T1tttt_2750_1_MC2017_fast \
T1tttt_2750_200_MC2017_fast \
T1tttt_2750_300_MC2017_fast \
T1tttt_2750_400_MC2017_fast \
T1tttt_2750_500_MC2017_fast \
T1tttt_2750_600_MC2017_fast \
T1tttt_2750_700_MC2017_fast \
T1tttt_2750_800_MC2017_fast \
T1tttt_2750_900_MC2017_fast \
T1tttt_2800_1000_MC2017_fast \
T1tttt_2800_100_MC2017_fast \
T1tttt_2800_1100_MC2017_fast \
T1tttt_2800_1200_MC2017_fast \
T1tttt_2800_1300_MC2017_fast \
T1tttt_2800_1400_MC2017_fast \
T1tttt_2800_1500_MC2017_fast \
T1tttt_2800_1600_MC2017_fast \
T1tttt_2800_1_MC2017_fast \
T1tttt_2800_200_MC2017_fast \
T1tttt_2800_300_MC2017_fast \
T1tttt_2800_400_MC2017_fast \
T1tttt_2800_500_MC2017_fast \
T1tttt_2800_600_MC2017_fast \
T1tttt_2800_700_MC2017_fast \
T1tttt_2800_800_MC2017_fast \
T1tttt_2800_900_MC2017_fast \
T1tttt_600_100_MC2017_fast \
T1tttt_600_1_MC2017_fast \
T1tttt_600_200_MC2017_fast \
T1tttt_600_300_MC2017_fast \
T1tttt_600_350_MC2017_fast \
T1tttt_600_375_MC2017_fast \
T1tttt_650_300_MC2017_fast \
T1tttt_650_350_MC2017_fast \
T1tttt_650_400_MC2017_fast \
T1tttt_650_425_MC2017_fast \
T1tttt_700_100_MC2017_fast \
T1tttt_700_1_MC2017_fast \
T1tttt_700_200_MC2017_fast \
T1tttt_700_300_MC2017_fast \
T1tttt_700_350_MC2017_fast \
T1tttt_700_400_MC2017_fast \
T1tttt_700_450_MC2017_fast \
T1tttt_700_475_MC2017_fast \
T1tttt_750_300_MC2017_fast \
T1tttt_750_350_MC2017_fast \
T1tttt_750_400_MC2017_fast \
T1tttt_750_450_MC2017_fast \
T1tttt_750_500_MC2017_fast \
T1tttt_750_525_MC2017_fast \
T1tttt_800_100_MC2017_fast \
T1tttt_800_1_MC2017_fast \
T1tttt_800_200_MC2017_fast \
T1tttt_800_300_MC2017_fast \
T1tttt_800_350_MC2017_fast \
T1tttt_800_400_MC2017_fast \
T1tttt_800_450_MC2017_fast \
T1tttt_800_500_MC2017_fast \
T1tttt_800_550_MC2017_fast \
T1tttt_800_575_MC2017_fast \
T1tttt_850_300_MC2017_fast \
T1tttt_850_350_MC2017_fast \
T1tttt_850_400_MC2017_fast \
T1tttt_850_450_MC2017_fast \
T1tttt_850_500_MC2017_fast \
T1tttt_850_550_MC2017_fast \
T1tttt_850_600_MC2017_fast \
T1tttt_850_625_MC2017_fast \
T1tttt_900_100_MC2017_fast \
T1tttt_900_1_MC2017_fast \
T1tttt_900_200_MC2017_fast \
T1tttt_900_300_MC2017_fast \
T1tttt_900_350_MC2017_fast \
T1tttt_900_400_MC2017_fast \
T1tttt_900_450_MC2017_fast \
T1tttt_900_500_MC2017_fast \
T1tttt_900_550_MC2017_fast \
T1tttt_900_600_MC2017_fast \
T1tttt_900_650_MC2017_fast \
T1tttt_900_675_MC2017_fast \
T1tttt_950_300_MC2017_fast \
T1tttt_950_350_MC2017_fast \
T1tttt_950_400_MC2017_fast \
T1tttt_950_450_MC2017_fast \
T1tttt_950_500_MC2017_fast \
T1tttt_950_550_MC2017_fast \
T1tttt_950_600_MC2017_fast \
T1tttt_950_650_MC2017_fast \
T1tttt_950_700_MC2017_fast \
T1tttt_950_725_MC2017_fast \
)