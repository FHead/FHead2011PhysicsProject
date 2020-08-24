google.charts.load('current', {packages: ['corechart', 'line']});
// google.charts.setOnLoadCallback(UpdateGraph);
var Chart;

function GetCurve(Version, Algorithm, Level, Curve, Label, HideBand)
{
   var Data = new google.visualization.DataTable();

   if(!(Version in JECData))
      return Data;
   if(!(Algorithm in JECData[Version]))
      return Data;
   if(!(Level in JECData[Version][Algorithm]))
      return Data;
   if(!(Curve in JECData[Version][Algorithm][Level]))
      return Data;

   var IsJERSF = false;
   if(Level == "JERSF")
      IsJERSF = true;
   
   Data.addColumn('number', "X");
   if(IsJERSF == false)
      Data.addColumn('number', Label);
   else
   {
      Data.addColumn('number', Label);
      Data.addColumn('number', Label + ' down');
      Data.addColumn('number', Label + ' up');
   }

   Data.addRows(JECData[Version][Algorithm][Level][Curve]["Data"]);

   if(HideBand == true && Data.getNumberOfColumns() > 2)
      Data.removeColumns(2, Data.getNumberOfColumns() - 2);

   var Formatter = new google.visualization.NumberFormat({pattern: '#.######'});
   Formatter.format(Data, 1);

   return Data;
}

function GetXTitle()
{
   var Titles = [];

   var CurveCount = $('#CurveCount').val();
   for(var i = 0; i < MaxCurveCount; i++)
      if(CurveCount > i)
         Titles.push($('#Curve'+(i+1)).val().split('_')[0]);

   Titles = Titles.sort().filter(function(a,b,c){return (b == c.indexOf(a));});   // sort + unique

   var Result = "";
   for(var Item in Titles)
   {
      if(Result != "")
         Result = Result + ", ";
      Result = Result + Titles[Item];
   }
   return Result;
}

function GetYTitle()
{
   var Titles = [];

   var CurveCount = $('#CurveCount').val();
   for(var i = 0; i < MaxCurveCount; i++)
   {
      if(CurveCount > i)
      {
         if($('#Level'+(i+1)).val() == 'Uncertainty')
            Titles.push("Uncertainty");
         else if($('#Level'+(i+1)).val().includes("Resolution"))
            Titles.push("Resolution");
         else if($('#Level'+(i+1)).val().includes("JERSF"))
            Titles.push("Resolution Scale Factor");
         else
            Titles.push("Correction");
      }
   }

   Titles = Titles.sort().filter(function(a,b,c){return (b == c.indexOf(a));});   // sort + unique

   var Result = "";
   for(var Item in Titles)
   {
      if(Result != "")
         Result = Result + ", ";
      Result = Result + Titles[Item];
   }
   return Result;
}

function GetLegendList()
{
   var KeepVersion = true;
   var KeepAlgorithm = true;
   var KeepLevel = true;
   var KeepCurve = true;
   
   var CurveCount = $('#CurveCount').val();

   var Versions = [];
   var Algorithms = [];
   var Levels = [];
   var Curves = [];
   
   for(var i = 0; i < MaxCurveCount; i++)
   {
      if(CurveCount <= i)
         continue;

      Versions.push($('#Version' + (i + 1)).val());
      Algorithms.push($('#Algorithm' + (i + 1)).val());
      Levels.push($('#Level' + (i + 1)).val());
      Curves.push($('#Curve' + (i + 1)).val());
   }

   if(Versions.every(function(value, i, array){return value == array[0]}) == true)
      KeepVersion = false;
   if(Algorithms.every(function(value, i, array){return value == array[0]}) == true)
      KeepAlgorithm = false;
   if(Levels.every(function(value, i, array){return value == array[0]}) == true)
      KeepLevel = false;
   if(Curves.every(function(value, i, array){return value == array[0]}) == true)
      KeepCurve = false;

   if(KeepVersion == false && KeepAlgorithm == false && KeepLevel == false && KeepCurve == false)
   {
      var FullList = Versions[0];
      FullList = FullList + ", " + Algorithms[0];
      FullList = FullList + ", " + Levels[0];
      FullList = FullList + ", " + Curves[0];
      return [FullList, "same", "same", "same", "same", "same", "same", "same"];
   }

   var Legend = ["", "", "", "", "", "", "", ""];

   for(var i = 0; i < MaxCurveCount; i++)
   {
      if(KeepVersion == true)
         if(CurveCount > i)
            Legend[i] = Legend[i] + ", " + Versions[i];
      if(KeepAlgorithm == true)
         if(CurveCount > i)
            Legend[i] = Legend[i] + ", " + Algorithms[i];
      if(KeepLevel == true)
         if(CurveCount > i)
            Legend[i] = Legend[i] + ", " + Levels[i];
      if(KeepCurve == true)
         if(CurveCount > i)
            Legend[i] = Legend[i] + ", " + Curves[i];
   }

   for(Item in Legend)
      Legend[Item] = Legend[Item].replace(/^, /, "");

   return Legend;
}

function UpdateGraph()
{
   var CurveCount = $('#CurveCount').val();

   var Legend = GetLegendList();

   var Data = GetCurve($('#Version1').val(), $('#Algorithm1').val(),
      $('#Level1').val(), $('#Curve1').val(),
      Legend[0], ($('#HideBand1:checked').length > 0));

   var Series = {};

   var CurrentSoFar = 0;
   if(Data.getNumberOfColumns() == 2)
   {
      Series[CurrentSoFar] = {};
      Series[CurrentSoFar]["color"] = DefaultColors[0];
      Series[CurrentSoFar]["lineWidth"] = DefaultWidth;
      Series[CurrentSoFar]["visibleInLegend"] = true;
   }
   else
   {
      Series[CurrentSoFar+0] = {};
      Series[CurrentSoFar+1] = {};
      Series[CurrentSoFar+2] = {};
      Series[CurrentSoFar+0]["color"] = DefaultColors[0];
      Series[CurrentSoFar+1]["color"] = DefaultColors[0];
      Series[CurrentSoFar+2]["color"] = DefaultColors[0];
      Series[CurrentSoFar+0]["lineWidth"] = DefaultWidth;
      Series[CurrentSoFar+1]["lineWidth"] = DefaultWidth / 2;
      Series[CurrentSoFar+2]["lineWidth"] = DefaultWidth / 2;
      Series[CurrentSoFar+0]["visibleInLegend"] = true;
      Series[CurrentSoFar+1]["visibleInLegend"] = false;
      Series[CurrentSoFar+2]["visibleInLegend"] = false;
   }

   for(var i = 1; i < MaxCurveCount; i++)
   {
      if(CurveCount > i)
      {
         CurrentSoFar = Data.getNumberOfColumns() - 1;
         
         var NewData = GetCurve($('#Version'+(i+1)).val(), $('#Algorithm'+(i+1)).val(),
            $('#Level'+(i+1)).val(), $('#Curve'+(i+1)).val(),
            Legend[i], ($('#HideBand'+(i+1)+':checked').length > 0));

         var Columns = [...Array(Data.getNumberOfColumns()).keys()];
         Columns.shift();
         var NewColumns = [...Array(NewData.getNumberOfColumns()).keys()];
         NewColumns.shift();
         
         Data = google.visualization.data.join(Data, NewData, 'full', [[0, 0]], Columns, NewColumns);

         if(NewData.getNumberOfColumns() == 2)
         {
            Series[CurrentSoFar] = {};
            Series[CurrentSoFar]["color"] = DefaultColors[i];
            Series[CurrentSoFar]["lineWidth"] = DefaultWidth;
            Series[CurrentSoFar]["visibleInLegend"] = true;
         }
         else
         {
            Series[CurrentSoFar+0] = {};
            Series[CurrentSoFar+1] = {};
            Series[CurrentSoFar+2] = {};
            Series[CurrentSoFar+0]["color"] = DefaultColors[i];
            Series[CurrentSoFar+1]["color"] = DefaultColors[i];
            Series[CurrentSoFar+2]["color"] = DefaultColors[i];
            Series[CurrentSoFar+0]["lineWidth"] = DefaultWidth;
            Series[CurrentSoFar+1]["lineWidth"] = DefaultWidth / 2;
            Series[CurrentSoFar+2]["lineWidth"] = DefaultWidth / 2;
            Series[CurrentSoFar+0]["visibleInLegend"] = true;
            Series[CurrentSoFar+1]["visibleInLegend"] = false;
            Series[CurrentSoFar+2]["visibleInLegend"] = false;
         }
      }
   }

   var XTitle = GetXTitle();
   var YTitle = GetYTitle();

   var ForceLinear = ($("#ForceLinear:checked").length > 0);

   var Options = Object.assign({}, DefaultOptions);
   Options["hAxis"]["title"] = XTitle;
   if(XTitle == "PT" && ForceLinear == false)
      Options["hAxis"]["scaleType"] = "log";
   else
      Options["hAxis"]["scaleType"] = "linear";
   Options["vAxis"]["title"] = YTitle;
   Options["series"] = Object.assign({}, Series);

   Chart = new google.visualization.LineChart(document.getElementById('ChartDiv'));
   Chart.draw(Data, Options);
}



