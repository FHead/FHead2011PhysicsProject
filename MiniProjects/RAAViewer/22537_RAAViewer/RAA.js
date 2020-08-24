var Chart;
var Plot;
var PlotData;
var XY;
var HashLockdown;

function UniqueValues(List, Field, Item)
{
   var Values = [];
   for(Index in List)
      Values.push(List[Index][Field]);
   Results = Values.filter(function(value, index, self) {return self.indexOf(value) == index;});

   Item.empty();
   for(var Index in Results)
      Item.append("<option value = \"" + Results[Index] + "\">" + Results[Index] + "</option>");
}

function FindRecord(System, Energy, Subject, Observable, Dependency, Centrality, Record, Selection)
{
   return Data.filter(function(item)
   {
      return item.System == System
         && item.Energy == Energy
         && item.Subject == Subject
         && item.Observable == Observable
         && item.Dependency == Dependency
         && item.Centrality == Centrality
         && item.Record == Record
         && item.Selection == Selection;
   });
}

function SetListOfSystems(Index)
{
   UniqueValues(Data, "System", $('#System'+Index));
   SetListOfEnergies(Index);
}

function SetListOfEnergies(Index)
{
   System = $('#System'+Index).val();
   UniqueValues(Data.filter(function(item)
   {
      return item.System == System;
   }), "Energy", $('#Energy'+Index));
   SetListOfSubjects(Index);
}

function SetListOfSubjects(Index)
{
   System = $('#System'+Index).val();
   Energy = $('#Energy'+Index).val();
   UniqueValues(Data.filter(function(item)
   {
      return item.System == System && item.Energy == Energy;
   }), "Subject", $('#Subject'+Index));
   SetListOfObservables(Index);
}

function SetListOfObservables(Index)
{
   System = $('#System'+Index).val();
   Energy = $('#Energy'+Index).val();
   Subject = $('#Subject'+Index).val();
   UniqueValues(Data.filter(function(item)
   {
      return item.System == System && item.Energy == Energy && item.Subject == Subject;
   }), "Observable", $('#Observable'+Index));
   SetListOfDependencies(Index);
}

function SetListOfDependencies(Index)
{
   System = $('#System'+Index).val();
   Energy = $('#Energy'+Index).val();
   Subject = $('#Subject'+Index).val();
   Observable = $('#Observable'+Index).val();
   UniqueValues(Data.filter(function(item)
   {
      return item.System == System && item.Energy == Energy && item.Subject == Subject
         && item.Observable == Observable;
   }), "Dependency", $('#Dependency'+Index));
   SetListOfCentralities(Index);
}

function SetListOfCentralities(Index)
{
   System = $('#System'+Index).val();
   Energy = $('#Energy'+Index).val();
   Subject = $('#Subject'+Index).val();
   Observable = $('#Observable'+Index).val();
   Dependency = $('#Dependency'+Index).val();
   UniqueValues(Data.filter(function(item)
   {
      return item.System == System && item.Energy == Energy && item.Subject == Subject
         && item.Observable == Observable && item.Dependency == Dependency;
   }), "Centrality", $('#Centrality'+Index));
   SetListOfRecords(Index);
}

function SetListOfRecords(Index)
{
   System = $('#System'+Index).val();
   Energy = $('#Energy'+Index).val();
   Subject = $('#Subject'+Index).val();
   Observable = $('#Observable'+Index).val();
   Dependency = $('#Dependency'+Index).val();
   Centrality = $('#Centrality'+Index).val();
   UniqueValues(Data.filter(function(item)
   {
      return item.System == System && item.Energy == Energy && item.Subject == Subject
         && item.Observable == Observable && item.Dependency == Dependency && item.Centrality == Centrality;
   }), "Record", $('#Record'+Index));
   SetListOfSelections(Index);
}

function SetListOfSelections(Index)
{
   System = $('#System'+Index).val();
   Energy = $('#Energy'+Index).val();
   Subject = $('#Subject'+Index).val();
   Observable = $('#Observable'+Index).val();
   Dependency = $('#Dependency'+Index).val();
   Centrality = $('#Centrality'+Index).val();
   Record = $('#Record'+Index).val();
   UniqueValues(Data.filter(function(item)
   {
      return item.System == System && item.Energy == Energy && item.Subject == Subject
         && item.Observable == Observable && item.Dependency == Dependency && item.Centrality == Centrality
         && item.Record == Record;
   }), "Selection", $('#Selection'+Index));
}

function SystemChange(Index)     {SetListOfEnergies(Index); UpdateCurves(); UpdateHash();}
function EnergyChange(Index)     {SetListOfSubjects(Index); UpdateCurves(); UpdateHash();}
function SubjectChange(Index)    {SetListOfObservables(Index); UpdateCurves(); UpdateHash();}
function ObservableChange(Index) {SetListOfDependencies(Index); UpdateCurves(); UpdateHash();}
function DependencyChange(Index) {SetListOfCentralities(Index); UpdateCurves(); UpdateHash();}
function CentralityChange(Index) {SetListOfRecords(Index); UpdateCurves(); UpdateHash();}
function RecordChange(Index)     {SetListOfSelections(Index); UpdateCurves(); UpdateHash();}
function SelectionChange(Index)  {UpdateCurves(); UpdateHash();}

function GetXY()
{
   var CurveCount = $("#CurveCount").val();

   Xs = [];
   Ys = [];
   XMin = 999;
   XMax = -999;
   YMin = 999;
   YMax = -999;

   for(Index = 0; Index < CurveCount; Index++)
   {
      System     = $('#System'+(Index+1)).val();
      Energy     = $('#Energy'+(Index+1)).val();
      Subject    = $('#Subject'+(Index+1)).val();
      Observable = $('#Observable'+(Index+1)).val();
      Dependency = $('#Dependency'+(Index+1)).val();
      Centrality = $('#Centrality'+(Index+1)).val();
      Record     = $('#Record'+(Index+1)).val();
      Selection  = $('#Selection'+(Index+1)).val();

      Item = Data.filter(function(item)
      {
         return item.System == System
            && item.Energy == Energy
            && item.Subject == Subject
            && item.Observable == Observable
            && item.Dependency == Dependency
            && item.Centrality == Centrality
            && item.Record == Record
            && item.Selection == Selection;
      });

      if(Item.length == 0)
         continue;

      Xs.push(Item[0].Dependency);
      Ys.push(Item[0].Observable);

      N = Item[0].X.length;
      for(i = 0; i < N; i++)
      {
         if(Item[0].X[i] - Item[0].EXLow[i] < XMin)
            XMin = Item[0].X[i] - Item[0].EXLow[i];
         if(Item[0].X[i] + Item[0].EXHigh[i] > XMax)
            XMax = Item[0].X[i] + Item[0].EXHigh[i];
         if(Item[0].Y[i] - Item[0].EYStatLow[i] < YMin)
            YMin = Item[0].Y[i] - Item[0].EYStatLow[i];
         if(Item[0].Y[i] + Item[0].EYStatHigh[i] > YMax)
            YMax = Item[0].Y[i] + Item[0].EYStatHigh[i];
         if(Item[0].Y[i] - Item[0].EYSysLow[i] < YMin)
            YMin = Item[0].Y[i] - Item[0].EYSysLow[i];
         if(Item[0].Y[i] + Item[0].EYSysHigh[i] > YMax)
            YMax = Item[0].Y[i] + Item[0].EYSysHigh[i];
      }
   }

   XMode = "";
   YMode = "";
   if($('#LogX')[0].checked)   XMode = "log";
   if($('#LogY')[0].checked)   YMode = "log";

   if(XMode == "")
   {
      DX = XMax - XMin;
      if(XMin != 0)
         XMin = XMin - DX * 0.05;
      XMax = XMax + DX * 0.05;
   }
   else
   {
      DX = Math.log(XMax) - Math.log(XMin);
      if(XMax / XMin < 10)
         DX = Math.log(10);
      XMin = XMin / Math.exp(DX * 0.05);
      XMax = XMax * Math.exp(DX * 0.05);
   }

   if(YMode == "")
   {
      DY = YMax - YMin;
      if(YMin != 0)
         YMin = YMin - DY * 0.05;
      YMax = YMax + DY * 0.05;
   }
   else
   {
      DY = Math.log(YMax) - Math.log(YMin);
      if(YMax / YMin < 10)
         DY = Math.log(10);
      YMin = YMin / Math.exp(DY * 0.05);
      YMax = YMax * Math.exp(DY * 0.05);
   }

   Xs = Xs.filter(function(value, index, self) {return self.indexOf(value) == index;});
   Ys = Ys.filter(function(value, index, self) {return self.indexOf(value) == index;});

   XLabel = '';
   for(i = 0; i < Xs.length; i++)
   {
      if(i != 0)
         XLabel += ',';
      XLabel += Xs[i];
   }
   YLabel = '';
   for(i = 0; i < Ys.length; i++)
   {
      if(i != 0)
         YLabel += ',';
      YLabel += Ys[i];
   }

   return {X: XLabel, Y: YLabel, XMin: XMin, XMax: XMax, YMin: YMin, YMax: YMax, XMode: XMode, YMode: YMode};
}

function UpdateCurves()
{
   // Set up plotting related stuff

   XY = GetXY();

   PlotOption =
   {
      xaxis:     {axisLabel: XY.X, min: XY.XMin, max: XY.XMax, mode: XY.XMode},
      yaxis:     {axisLabel: XY.Y, min: XY.YMin, max: XY.YMax, mode: XY.YMode},
      grid:      {margin: 20},
      selection: {mode: "xy"}
   };
   if(XY.XMode == "log")
   {
      PlotOption.xaxis["transform"] = function(v) {return v > 0 ? Math.log(v) / Math.LN10 : null;};
      PlotOption.xaxis["inverseTransform"] = function(v) {return Math.pow(10, v);};
   }
   if(XY.YMode == "log")
   {
      PlotOption.yaxis["transform"] = function(v) {return v > 0 ? Math.log(v) / Math.LN10 : null;};
      PlotOption.yaxis["inverseTransform"] = function(v) {return Math.pow(10, v);};
   }

   var CurveCount = $("#CurveCount").val();

   PlotData = [];

   for(Index = 0; Index < CurveCount; Index++)
   {
      System     = $('#System'+(Index+1)).val();
      Energy     = $('#Energy'+(Index+1)).val();
      Subject    = $('#Subject'+(Index+1)).val();
      Observable = $('#Observable'+(Index+1)).val();
      Dependency = $('#Dependency'+(Index+1)).val();
      Centrality = $('#Centrality'+(Index+1)).val();
      Record     = $('#Record'+(Index+1)).val();
      Selection  = $('#Selection'+(Index+1)).val();

      Item = Data.filter(function(item)
      {
         return item.System == System
            && item.Energy == Energy
            && item.Subject == Subject
            && item.Observable == Observable
            && item.Dependency == Dependency
            && item.Centrality == Centrality
            && item.Record == Record
            && item.Selection == Selection;
      });

      if(Item.length == 0)
         continue;

      N = Item[0]["X"].length;

      var DTotal = [];
      var DStat = [];
      for(i = 0; i < N; i++)
      {
         DStat.push([Item[0].X[i], Item[0].Y[i],
            Item[0].EXLow[i], Item[0].EXHigh[i],
            Item[0].EYStatLow[i], Item[0].EYStatHigh[i]]);

         EYStatLow  = Item[0].EYStatLow[i];
         EYStatHigh = Item[0].EYStatHigh[i];
         EYSysLow   = Item[0].EYSysLow[i];
         EYSysHigh  = Item[0].EYSysHigh[i];
         Global     = Item[0].GlobalUncertainty;

         EYLow = Math.sqrt(EYStatLow * EYStatLow + EYSysLow * EYSysLow + Global * Global);
         EYHigh = Math.sqrt(EYStatHigh * EYStatHigh + EYSysHigh * EYSysHigh + Global * Global);
         
         DTotal.push([Item[0].X[i], Item[0].Y[i],
            Item[0].EXLow[i], Item[0].EXHigh[i],
            EYLow, EYHigh]);
      }
      var DPStat =
      {
         show: true,
         radius: 5,
         fillColor: DefaultColors[Index],
         errorbars: "xy",
         xerr: {show: true, asymmetric: true},
         yerr: {show: true, asymmetric: true, upperCap: '-', lowerCap: '-'}
      };
      var DPTotal =
      {
         show: true,
         radius: 5,
         fillColor: DefaultColors[Index],
         errorbars: "xy",
         xerr: {show: true, asymmetric: true},
         yerr: {show: true, asymmetric: true}
      };

      PlotData.push({color: DefaultColors[Index], points: DPStat, data: DStat});
      PlotData.push({color: DefaultColors[Index], points: DPTotal, data: DTotal});
   }

   Plot = $.plot("#ChartDiv", PlotData, PlotOption);
}

function ResetRange()
{
   $.each(Plot.getXAxes(), function(_,axis)
   {
      var opts = axis.options;
      opts.min = XY.XMin;
      opts.max = XY.XMax;
   });
   $.each(Plot.getYAxes(), function(_,axis)
   {
      var opts = axis.options;
      opts.min = XY.YMin;
      opts.max = XY.YMax;
   });
   Plot.setupGrid();
   Plot.draw();
   Plot.clearSelection();
}

function ShowHideSelector()
{
   var CurveCount = $('#CurveCount').val();
   if(CurveCount > MaxCurveCount || CurveCount <= 0)
      CurveCount = 1;
   for(var i = 0; i < MaxCurveCount; i++)
      $('#Selector'+(i+1)).css('display', (CurveCount > i) ? "block" : "none");
}

function UpdateHash()
{
   if(HashLockdown == true)
      return;

   var HashString = "";
   var CurveCount = $('#CurveCount').val();

   // TODO: check if "+", ",", "&" could be used in any of the fields.  If yes, change

   for(var i = 0; i < MaxCurveCount; i++)
   {
      if(CurveCount <= i)
         continue;
      if(i != 0)
         HashString = HashString + "+";
      HashString = HashString
         + $('#System'+(i+1)).val() + ","
         + $('#Energy'+(i+1)).val() + ","
         + $('#Subject'+(i+1)).val() + ","
         + $('#Observable'+(i+1)).val() + ","
         + $('#Dependency'+(i+1)).val() + ","
         + $('#Centrality'+(i+1)).val() + ","
         + $('#Record'+(i+1)).val() + ","
         + $('#Selection'+(i+1)).val();
   }

   HashString = HashString + "&" + "LogX=" + $('#LogX:checked').length;
   HashString = HashString + "&" + "LogY=" + $('#LogY:checked').length;

   HashString = encodeURI(HashString);

   window.location.hash = HashString;
}

function LoadFromHash()
{
   var HashString = window.location.hash;
   HashString = HashString.replace(/^#/, "");
   HashString = decodeURI(HashString);

   HashLockdown = true;

   if(HashString == "")
   {
      LoadDefaultSetup();
      return;
   }

   var Curves = HashString.split('&')[0].split("+");
   var ExtraInformation = HashString.split('&');
   ExtraInformation.shift();

   CurveCount = Curves.length;
   if(CurveCount > MaxCurveCount)
      CurveCount = MaxCurveCount;
   $('#CurveCount').val(CurveCount);

   var Error = false;

   for(var i = 0; i < MaxCurveCount; i++)
   {
      if(CurveCount <= i)
         continue;

      var Split = Curves[i].split(',');
      var Items = FindRecord(Split[0], Split[1], Split[2], Split[3], Split[4], Split[5], Split[6], Split[7]);
      if(Items.length == 0)
      {
         console.log(Split);
         Error = true;
         break;
      }

      $('#System'+(i+1)).val(Split[0]);
      SystemChange(i + 1);
      $('#Energy'+(i+1)).val(Split[1]);
      EnergyChange(i + 1);
      $('#Subject'+(i+1)).val(Split[2]);
      SubjectChange(i + 1);
      $('#Observable'+(i+1)).val(Split[3]);
      ObservableChange(i + 1);
      $('#Dependency'+(i+1)).val(Split[4]);
      DependencyChange(i + 1);
      $('#Centrality'+(i+1)).val(Split[5]);
      CentralityChange(i + 1);
      $('#Record'+(i+1)).val(Split[6]);
      RecordChange(i + 1);
      $('#Selection'+(i+1)).val(Split[7]);
      SelectionChange(i + 1);
   }

   if(Error == true)
   {
      LoadDefaultSetup();
      return;
   }

   for(var i = 0; i < ExtraInformation.length; i++)
   {
      if(ExtraInformation[i] == "LogX=0")
         $('#LogX').prop("checked", false);
      if(ExtraInformation[i] == "LogX=1")
         $('#LogX').prop("checked", true);
      if(ExtraInformation[i] == "LogY=0")
         $('#LogY').prop("checked", false);
      if(ExtraInformation[i] == "LogY=1")
         $('#LogY').prop("checked", true);
   }

   HashLockdown = false;
}

function LoadDefaultSetup()
{
   $('#CurveCount').val(1);

   $('#System'+(i+1)).prop("selectedIndex", 0);
   SystemChange(i + 1);
   $('#Energy'+(i+1)).prop("selectedIndex", 0);
   EnergyChange(i + 1);
   $('#Subject'+(i+1)).prop("selectedIndex", 0);
   SubjectChange(i + 1);
   $('#Observable'+(i+1)).prop("selectedIndex", 0);
   ObservableChange(i + 1);
   $('#Dependency'+(i+1)).prop("selectedIndex", 0);
   DependencyChange(i + 1);
   $('#Centrality'+(i+1)).prop("selectedIndex", 0);
   CentralityChange(i + 1);
   $('#Record'+(i+1)).prop("selectedIndex", 0);
   RecordChange(i + 1);
   $('#Selection'+(i+1)).prop("selectedIndex", 0);
   SelectionChange(i + 1);

   $('LogX').prop("checked", true);
   $('LogY').prop("checked", false);

   HashLockdown = false;
}

function Initialize()
{
   console.log('starting initialize function');

   HashLockdown = false;

   for(i = MaxCurveCount; i >= 1; i--)
   {
      SelectorDiv = "";
      SelectorDiv += '<div class="Selector" id="Selector' + i + '">';
      SelectorDiv += '   <div class="color" id="Color' + i + '"></div>';
      SelectorDiv += '   System <select id="System' + i + '"></select>';
      SelectorDiv += '   Energy <select id="Energy' + i + '"></select>';
      SelectorDiv += '   Object <select id="Subject' + i + '"></select>';
      SelectorDiv += '   Observable <select id="Observable' + i + '"></select>';
      SelectorDiv += '   Dependency <select id="Dependency' + i + '"></select>';
      SelectorDiv += '   Centrality <select id="Centrality' + i + '"></select>';
      SelectorDiv += '   Record <select id="Record' + i + '"></select>';
      SelectorDiv += '   Selection <select id="Selection' + i + '"></select>';
      SelectorDiv += '</div>';
      $('#SelectorN').after(SelectorDiv);

      $('#System'+i)    .attr("Index", i);
      $('#Energy'+i)    .attr("Index", i);
      $('#Subject'+i)   .attr("Index", i);
      $('#Observable'+i).attr("Index", i);
      $('#Dependency'+i).attr("Index", i);
      $('#Centrality'+i).attr("Index", i);
      $('#Record'+i)    .attr("Index", i);
      $('#Selection'+i) .attr("Index", i);

      $('#Color'+i).css('background-color', DefaultColors[i-1]);
      $('#System'+i)    .change(function(){SystemChange($(this).attr("Index"));});
      $('#Energy'+i)    .change(function(){EnergyChange($(this).attr("Index"));});
      $('#Subject'+i)   .change(function(){SubjectChange($(this).attr("Index"));});
      $('#Observable'+i).change(function(){ObservableChange($(this).attr("Index"));});
      $('#Dependency'+i).change(function(){DependencyChange($(this).attr("Index"));});
      $('#Centrality'+i).change(function(){CentralityChange($(this).attr("Index"));});
      $('#Record'+i)    .change(function(){RecordChange($(this).attr("Index"));});
      $('#Selection'+i) .change(function(){SelectionChange($(this).attr("Index"));});

      SetListOfSystems(i);
   }

   LoadFromHash();

   $('#CurveCount').change(function(){ShowHideSelector(); UpdateCurves(); UpdateHash();});
   UpdateCurves();
   UpdateHash();
   ShowHideSelector();

   $('#ChartDiv').bind("plotselected", function(event, ranges)
   {
      $.each(Plot.getXAxes(), function(_,axis)
      {
         var opts = axis.options;
         opts.min = ranges.xaxis.from;
         opts.max = ranges.xaxis.to;
      });
      $.each(Plot.getYAxes(), function(_,axis)
      {
         var opts = axis.options;
         opts.min = ranges.yaxis.from;
         opts.max = ranges.yaxis.to;
      });
      Plot.setupGrid();
      Plot.draw();
      Plot.clearSelection();
   });

   $('#LogX').change(function(){UpdateCurves(); UpdateHash();});
   $('#LogY').change(function(){UpdateCurves(); UpdateHash();});

   $('#ChartDiv').bind("contextmenu", function(){ResetRange(); return false;});
   $('#ZoomOutButton').click(function() {ResetRange();});

   $('#DownloadButton').click(function(e)
   {
      e.preventDefault();
      html2canvas($('#ChartDiv')[0]).then(canvas =>
      {
         console.log("X");
         document.body.appendChild(canvas);
         
         var Width = $('#ChartDiv').width() / 48.0;
         var Height = $('#ChartDiv').height() / 48.0 - 0.2;
         var PdfFile = new jsPDF({orientation: 'landscape', unit: 'in', format: [Width, Height],
            compressPdf: true});
         PdfFile.addImage({imageData: canvas.toDataURL("image/png"), x: -0.25, y: -0.1, compression: 'SLOW'});
         PdfFile.save('HIChart.pdf');

         document.body.removeChild(canvas);
      });
   });

   // $('#DownloadButton').click(function()
   // {
   //    // I think default is 96 dpi?
   //    var Width = $('#ChartDiv').width() / 96.0 * 2;
   //    var Height = $('#ChartDiv').height() / 96.0 * 2;
   //    var PdfFile = new jsPDF({orientation: 'landscape', unit: 'in', format: [Width, Height], compressPdf: true});
   //    PdfFile.addImage({imageData: $('.flot-overlay')[0].toDataURL("image/png"), x: 0, y: 0, compression: 'SLOW'});
   //    PdfFile.save('HIChart.pdf');
   // });
}

$(window).on('load', Initialize);



