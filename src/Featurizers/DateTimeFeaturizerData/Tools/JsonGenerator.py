# ----------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License
# ----------------------------------------------------------------------
"""Generates JSON files based on data previously pickled"""

import lzma
import os
import pickle
import sys
import json

# Note that this isn't used directly, but is required by the picked python content
import pandas as pd

import CommonEnvironment
from CommonEnvironment import CommandLine
from CommonEnvironment import FileSystem
from CommonEnvironment.StreamDecorator import StreamDecorator

# ----------------------------------------------------------------------
_script_fullpath                            = CommonEnvironment.ThisFullpath()
_script_dir, _script_name                   = os.path.split(_script_fullpath)
# ----------------------------------------------------------------------

@CommandLine.EntryPoint(
)
@CommandLine.Constraints(
    zipped_input_filename=CommandLine.FilenameTypeInfo(),
    output_stream=None,
)
def EntryPoint(
    zipped_input_filename,
    output_stream=sys.stdout,
):
    """Generates JSON files based on data previously pickled"""

    with StreamDecorator(output_stream).DoneManager(
        line_prefix="",
        prefix="\nResults: ",
        suffix="\n",
    ) as dm:
        output_dir = os.path.join(_script_dir, "..", "GeneratedCode")

        FileSystem.RemoveTree(output_dir)
        FileSystem.MakeDirs(output_dir)

        df = _holiday_data_loader(zipped_input_filename)
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

            jsonPath = os.path.join(output_dir, "{}.json".format(countryName))
            with open(jsonPath, 'w') as f:
                json.dump(out, f)

        return dm.result

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
def _holiday_data_loader(_path):
    """Load holiday data as a static initializer."""
    with lzma.open(_path, "rb") as fr:
        df = pickle.loads(fr.read())
        df['countryRegionCode'] = df['countryRegionCode'] \
            .apply(lambda x: x if type(x) == str else None)
        df['isPaidTimeOff'] = df['isPaidTimeOff'] \
            .apply(lambda x: x if type(x) == bool else None)
        return df

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
if __name__ == "__main__":
    try:
        sys.exit(CommandLine.Main())
    except KeyboardInterrupt:
        pass
