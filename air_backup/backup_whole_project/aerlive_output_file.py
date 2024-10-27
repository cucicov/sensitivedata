import pandas as pd

# Function to read and process the CSV file
def process_csv(file_path, output_file):
    # Read the CSV file
    df = pd.read_csv(file_path, delimiter=';')

    # Strip any leading/trailing whitespace from column names
    df.columns = df.columns.str.strip()

    # Check for expected columns
    expected_columns = ['cluster', 'eui', 'Data-Ora', 'pm10', 'pm2.5', 'gps_lat', 'gps_lon', 'senzor', 'Ora', 'Ziua', 'Data']
    actual_columns = df.columns.tolist()
    missing_columns = [col for col in expected_columns if col not in actual_columns]
    
    if missing_columns:
        with open(output_file, 'a') as f:
            f.write("The following expected columns are missing in the CSV file: {}\n".format(missing_columns))
            f.write("Actual columns in the CSV file: {}\n".format(actual_columns))
        return

    # Convert 'Data' and 'Ora' columns to datetime for sorting
    df['Data'] = pd.to_datetime(df['Data'], format='%m/%d/%Y')
    df['Ora'] = pd.to_timedelta(df['Ora'].astype(str) + ':00:00')

    # Filter records for the year 2023
    df_2023 = df[df['Data'].dt.year == 2023]

    # Replace commas with periods and convert to numeric
    numeric_columns = ['pm10', 'pm2.5']
    for column in numeric_columns:
        df_2023[column] = df_2023[column].str.replace(',', '.').astype(float)

    # Group by year, month, and day to calculate daily averages
    df_2023['Year'] = df_2023['Data'].dt.year
    df_2023['Month'] = df_2023['Data'].dt.month
    df_2023['Day'] = df_2023['Data'].dt.day

    grouped = df_2023.groupby(['Year', 'Month', 'Day'])

    # Calculate mean for relevant numeric columns and reset index
    daily_averages = grouped[numeric_columns].mean().reset_index()

    # Write the daily averages for each day of each month in 2023 to the file
    with open(output_file, 'a') as f:
        for _, row in daily_averages.iterrows():
            f.write("Date: {}-{}-{}\n".format(int(row['Year']), int(row['Month']), int(row['Day'])))
            f.write("Average PM10: {:.2f}, Average PM2.5: {:.2f}\n\n".format(row['pm10'], row['pm2.5']))

        # Calculate and write the minimum and maximum values from the averages
        min_pm10 = daily_averages['pm10'].min()
        max_pm10 = daily_averages['pm10'].max()
        min_pm2_5 = daily_averages['pm2.5'].min()
        max_pm2_5 = daily_averages['pm2.5'].max()

        f.write("Minimum and Maximum Average Values for 2023:\n")
        f.write("PM10: Min = {:.2f}, Max = {:.2f}\n".format(min_pm10, max_pm10))
        f.write("PM2.5: Min = {:.2f}, Max = {:.2f}\n".format(min_pm2_5, max_pm2_5))

# Main script execution
if __name__ == "__main__":
    # Specify the path to your CSV file
    csv_file_path = 'allyear.csv'
    output_file_path = 'output_results.txt'
    
    # Process the CSV and write output to the file
    process_csv(csv_file_path, output_file_path)
