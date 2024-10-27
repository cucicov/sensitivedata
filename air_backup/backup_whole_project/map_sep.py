# Function to map PM2.5 values from the original range to the new range
def map_pm25_values(pm25_values, min_orig, max_orig, min_new, max_new):
    return [min_new + (value - min_orig) * (max_new - min_new) / (max_orig - min_orig) for value in pm25_values]

# Original PM2.5 values with corresponding dates for September 2023
pm25_data_september = [
("2023-2-1", 31.44), ("2023-2-2", 10.29), ("2023-2-3", 11.30), ("2023-2-4", 19.10), ("2023-2-5", 9.43),
("2023-2-6", 15.58), ("2023-2-7", 18.46), ("2023-2-8", 18.71), ("2023-2-9", 29.42), ("2023-2-10", 42.10),
("2023-2-11", 43.16), ("2023-2-12", 51.94), ("2023-2-13", 47.45), ("2023-2-14", 58.80), ("2023-2-15", 44.41),
("2023-2-16", 46.91), ("2023-2-17", 52.15), ("2023-2-18", 23.95), ("2023-2-19", 12.34), ("2023-2-20", 7.90),
("2023-2-21", 6.40), ("2023-2-22", 13.70), ("2023-2-23", 9.04), ("2023-2-24", 16.97), ("2023-2-25", 34.77),
("2023-2-26", 23.95), ("2023-2-27", 9.39), ("2023-2-28", 19.20)
]

# Extract the dates and PM2.5 values into separate lists for September 2023
dates_september, pm25_values_september = zip(*pm25_data_september)

# Define the original and new ranges for PM2.5
min_orig = 7
max_orig = 120
min_new = 1
max_new = 10

# Map the values for September 2023
mapped_values_september = map_pm25_values(pm25_values_september, min_orig, max_orig, min_new, max_new)

# Print the original and mapped values with the corresponding dates for September 2023
for date, original_value, mapped_value in zip(dates_september, pm25_values_september, mapped_values_september):
    print("Date: {} | Original PM10: {:.2f} | Mapped PM10: {:.2f}".format(date, original_value, mapped_value))
