using Microsoft.ML.Data;
using System;
using System.IO;
using Xunit;

namespace Microsoft.ML.Autogen
{
    public class DateTimeFeaturizerTests
    {
        [Fact]
        public void CorrectNumberOfColumns()
        {
            MLContext mlContext = new MLContext(1);
            var path = Path.Combine(Environment.CurrentDirectory, "TestData", "dates.txt");

            var loader = mlContext.Data.CreateTextLoader(
                new[] {
                        new TextLoader.Column("date", DataKind.DateTime, 0)
                }
            );
            IDataView data = loader.Load(path);

            // Build the pipeline, fit, and transform it.
            var dateColumn = data.Schema["date"];
            var columnPrefix = "DTC";
            var pipeline = mlContext.Transforms.DateTimeTransformer(dateColumn, columnPrefix);
            var model = pipeline.Fit(data);
            var output = model.Transform(data);
            var schema = output.Schema;

            // Check the schema has 11 columns
            Assert.Equal(11, schema.Count);

            // Make sure names with prefix and order are correct
            Assert.Equal($"{columnPrefix}_year", schema[1].Name);
            Assert.Equal($"{columnPrefix}_month", schema[2].Name);
            Assert.Equal($"{columnPrefix}_day", schema[3].Name);
            Assert.Equal($"{columnPrefix}_hour", schema[4].Name);
            Assert.Equal($"{columnPrefix}_minute", schema[5].Name);
            Assert.Equal($"{columnPrefix}_second", schema[6].Name);
            Assert.Equal($"{columnPrefix}_dayOfWeek", schema[7].Name);
            Assert.Equal($"{columnPrefix}_dayOfYear", schema[8].Name);
            Assert.Equal($"{columnPrefix}_quarterOfYear", schema[9].Name);
            Assert.Equal($"{columnPrefix}_weekOfMonth", schema[10].Name);

            // Make sure types are correct
            Assert.Equal(typeof(int), schema[1].Type.RawType);
            Assert.Equal(typeof(byte), schema[2].Type.RawType);
            Assert.Equal(typeof(byte), schema[3].Type.RawType);
            Assert.Equal(typeof(byte), schema[4].Type.RawType);
            Assert.Equal(typeof(byte), schema[5].Type.RawType);
            Assert.Equal(typeof(byte), schema[6].Type.RawType);
            Assert.Equal(typeof(byte), schema[7].Type.RawType);
            Assert.Equal(typeof(ushort), schema[8].Type.RawType);
            Assert.Equal(typeof(byte), schema[9].Type.RawType);
            Assert.Equal(typeof(byte), schema[10].Type.RawType);
        }

        [Fact]
        public void CanUseDateFromColumn()
        {
            MLContext mlContext = new MLContext(1);
            var path = Path.Combine(Environment.CurrentDirectory, "TestData", "dates.txt");

            var loader = mlContext.Data.CreateTextLoader(
                new[] {
                        new TextLoader.Column("date", DataKind.DateTime, 0)
                }
            );
            IDataView data = loader.Load(path);

            // Build the pipeline, fit, and transform it.
            var dateColumn = data.Schema["date"];
            var pipeline = mlContext.Transforms.DateTimeTransformer(dateColumn, "DTC");
            var model = pipeline.Fit(data);
            var output = model.Transform(data);

            // Get the data from the first row and make sure it matches expected
            var row = output.Preview(1).RowView[0].Values;

            // Assert the data from the first row is what we expect
            Assert.Equal(2019, row[1].Value);
            Assert.Equal((byte)6, row[2].Value);
            Assert.Equal((byte)29, row[3].Value);
            Assert.Equal((byte)0, row[4].Value);
            Assert.Equal((byte)1, row[5].Value);
            Assert.Equal((byte)0, row[6].Value);
            Assert.Equal((byte)6, row[7].Value);
            Assert.Equal((ushort)179, row[8].Value);
            Assert.Equal((byte)2, row[9].Value);
            Assert.Equal((byte)4, row[10].Value);
        }

        [Fact]
        public void CanUseRawDate()
        {
            MLContext mlContext = new MLContext(1);
            var path = Path.Combine(Environment.CurrentDirectory, "TestData", "dates.txt");

            var loader = mlContext.Data.CreateTextLoader(
                new[] {
                        new TextLoader.Column("date", DataKind.DateTime, 0)
                }
            );
            IDataView data = loader.Load(path);

            // Build the pipeline, fit, and transform it.
            var date = DateTime.Parse("2019-06-29 12:01:00 AM");
            var pipeline = mlContext.Transforms.DateTimeTransformer(date, "DTC");
            var model = pipeline.Fit(data);
            var output = model.Transform(data);

            // Get the data from the first row and make sure it matches expected
            var row = output.Preview(1).RowView[0].Values;

            // Assert the data from the first row is what we expect
            Assert.Equal(2019, row[1].Value);
            Assert.Equal((byte)6, row[2].Value);
            Assert.Equal((byte)29, row[3].Value);
            Assert.Equal((byte)0, row[4].Value);
            Assert.Equal((byte)1, row[5].Value);
            Assert.Equal((byte)0, row[6].Value);
            Assert.Equal((byte)6, row[7].Value);
            Assert.Equal((ushort)179, row[8].Value);
            Assert.Equal((byte)2, row[9].Value);
            Assert.Equal((byte)4, row[10].Value);
        }

    }

}
