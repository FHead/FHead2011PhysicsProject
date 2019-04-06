google.charts.load('current', {packages: ['corechart', 'line']});
// google.charts.setOnLoadCallback(UpdateGraph);
var Chart;

function GetCurve(Version, Algorithm, Level, Curve, Label)
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

   Data.addColumn('number', "X");
   Data.addColumn('number', Label);

   Data.addRows(JECData[Version][Algorithm][Level][Curve]["Data"]);

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
      Legend[0]);

   var Column = [];
   for(var i = 1; i < MaxCurveCount; i++)
   {
      if(CurveCount > i)
      {
         var NewData = GetCurve($('#Version'+(i+1)).val(), $('#Algorithm'+(i+1)).val(),
            $('#Level'+(i+1)).val(), $('#Curve'+(i+1)).val(),
            Legend[i]);
         Column.push(i);
         Data = google.visualization.data.join(Data, NewData, 'full', [[0, 0]], Column, [1]);
      }
   }

   var XTitle = GetXTitle();
   var YTitle = GetYTitle();

   var Options = DefaultOptions;
   Options["hAxis"]["title"] = XTitle;
   if(XTitle == "PT")
      Options["hAxis"]["scaleType"] = "log";
   else
      Options["hAxis"]["scaleType"] = "linear";
   Options["vAxis"]["title"] = YTitle;

   Chart = new google.visualization.LineChart(document.getElementById('ChartDiv'));
   Chart.draw(Data, Options);
}



