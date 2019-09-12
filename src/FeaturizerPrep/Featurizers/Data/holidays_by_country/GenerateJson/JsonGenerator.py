import pandas as pd
import lzma
import pickle
import sys
import simplejson as json

def jsonKeys2Int(x):
    if isinstance(x, dict):
        return {int(k): v for k, v in x.items()}
    return x

def _holiday_data_loader(_path):
    """Load holiday data as a static initializer."""
    with lzma.open(_path, "rb") as fr:
        df = pickle.loads(fr.read())
        df['countryRegionCode'] = df['countryRegionCode'] \
            .apply(lambda x: x if type(x) == str else None)
        df['isPaidTimeOff'] = df['isPaidTimeOff'] \
            .apply(lambda x: x if type(x) == bool else None)
        return df


if __name__ == "__main__":

    df = _holiday_data_loader(str(sys.argv[1]))
    #with open('holidays.json', 'w') as f:
        #f.write(df.to_json(orient='records', lines=True))

    allCountryNames = list(set((df['countryOrRegion'])))

    for countryName in allCountryNames:

        dfByCountry = df.loc[df['countryOrRegion'] == countryName]

        date = [int(x.timestamp()) for x in list(dfByCountry['date'])]
        name = list(dfByCountry['normalizeHolidayName'])
        
        date_dict = {"Date" : date}
        name_dict = {"Holiday" : name}

        out = {}
        out.update(date_dict)
        out.update(name_dict)

        jsonPath = "../" + countryName + ".json"
        with open(jsonPath, 'w') as f:
            json.dump(out, f)
        f.close()