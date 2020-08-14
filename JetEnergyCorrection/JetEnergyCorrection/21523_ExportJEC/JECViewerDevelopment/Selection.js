function SetListOfVersions(Item)
{
   Item.empty();
   for(var key in JECData)
      Item.append("<option value=\"" + key + "\">" + key + "</option>");
}

function SetListOfAlgorithms(VersionItem, Item)
{
   Item.empty();

   var Version = VersionItem.val();

   if(Version in JECData)
      for(var key in JECData[Version])
         Item.append("<option value=\"" + key + "\">" + key + "</option>");
   else
      Item.append("<option value=\"NA\">N/A</option>");
}

function SetListOfLevels(VersionItem, AlgorithmItem, Item)
{
   Item.empty();

   var Version = VersionItem.val();
   var Algorithm = AlgorithmItem.val();

   if((Version in JECData) && (Algorithm in JECData[Version]))
      for(var key in JECData[Version][Algorithm])
         Item.append("<option value=\"" + key + "\">" + key + "</option>");
   else
      Item.append("<option value=\"NA\">N/A</option>");
}

function SetListOfCurves(VersionItem, AlgorithmItem, LevelItem, Item)
{
   Item.empty();

   var Version = VersionItem.val();
   var Algorithm = AlgorithmItem.val();
   var Level = LevelItem.val();

   if((Version in JECData) && (Algorithm in JECData[Version]) && (Level in JECData[Version][Algorithm]))
      for(var key in JECData[Version][Algorithm][Level])
         Item.append("<option value=\"" + key + "\">" + key + "</option>");
   else
      Item.append("<option value=\"NA\">N/A</option>");
}

function ShowHideSelector()
{
   var CurveCount = $('#CurveCount').val();
   if(CurveCount > MaxCurveCount || CurveCount <= 0)
      CurveCount = 1;

   for(var i = 0; i < MaxCurveCount; i++)
   {
      if(CurveCount > i)
         Value = 'block';
      else
         Value = 'none';
      $('#Selector'+(i+1)).css('display', Value);
   }
}

function CheckAlgorithms(VersionItem, Item)
{
   var Version = VersionItem.val();
   var Algorithm = Item.val();

   if(Algorithm in JECData[Version])
      return true;
   else
      return false;
}

function CheckLevels(VersionItem, AlgorithmItem, Item)
{
   var Version = VersionItem.val();
   var Algorithm = AlgorithmItem.val();
   var Level = Item.val();

   if((Algorithm in JECData[Version]) && (Level in JECData[Version][Algorithm]))
      return true;
   else
      return false;
}

function CheckCurves(VersionItem, AlgorithmItem, LevelItem, Item)
{
   var Version = VersionItem.val();
   var Algorithm = AlgorithmItem.val();
   var Level = LevelItem.val();
   var Curve = Item.val();

   // console.log("CheckCurve " + Version);
   // console.log("CheckCurve " + Algorithm);
   // console.log("CheckCurve " + Level);
   // console.log("CheckCurve " + Curve);
   // console.log(Item);
   // console.log(Item.val());

   if((Algorithm in JECData[Version]) && (Level in JECData[Version][Algorithm])
      && (Curve in JECData[Version][Algorithm][Level]))
      return true;
   else
      return false;
}

function VersionChange(VersionItem, AlgorithmItem, LevelItem, CurveItem)
{
   var Algorithm = "";
   if(CheckAlgorithms(VersionItem, AlgorithmItem) == true)
      Algorithm = AlgorithmItem.val();

   SetListOfAlgorithms(VersionItem, AlgorithmItem);

   if(Algorithm != "")
      AlgorithmItem.val(Algorithm);

   AlgorithmChange(VersionItem, AlgorithmItem, LevelItem, CurveItem);
}

function AlgorithmChange(VersionItem, AlgorithmItem, LevelItem, CurveItem)
{
   var Level = "";
   if(CheckLevels(VersionItem, AlgorithmItem, LevelItem) == true)
      Level = LevelItem.val();

   SetListOfLevels(VersionItem, AlgorithmItem, LevelItem);

   if(Level != "")
      LevelItem.val(Level);

   LevelChange(VersionItem, AlgorithmItem, LevelItem, CurveItem);
}

function LevelChange(VersionItem, AlgorithmItem, LevelItem, CurveItem)
{
   var Curve = "";
   if(CheckCurves(VersionItem, AlgorithmItem, LevelItem, CurveItem) == true)
      Curve = CurveItem.val();

   // console.log("LevelChange" + Curve);

   SetListOfCurves(VersionItem, AlgorithmItem, LevelItem, CurveItem);

   if(Curve != "")
      CurveItem.val(Curve);

   CurveChange(VersionItem, AlgorithmItem, LevelItem, CurveItem);
}

function CurveChange(VersionItem, AlgorithmItem, LevelItem, CurveItem)
{
}

function LoadDefaultSetup()
{
   $('#CurveCount').val(3);

   var Version = "Autumn18_RunA_V8_DATA";
   var Algorithm = "AK4PFchs";
   var Level = "L1FastJet";
   var Curve = "Eta_Rho40.00_PT100.00";

   if(Version in JECData)                            $("#Version1").val(Version);
   if(Algorithm in JECData[Version])                 $("#Algorithm1").val(Algorithm);
   if(Level in JECData[Version][Algorithm])          $("#Level1").val(Level);
   if(Curve in JECData[Version][Algorithm][Level])   $("#Curve1").val(Curve);
   
   Version = "Autumn18_RunA_V8_DATA";
   Algorithm = "AK4PFchs";
   Level = "L2Relative";
   Curve = "Eta_Rho40.00_PT100.00";

   if(Version in JECData)                            $("#Version2").val(Version);
   if(Algorithm in JECData[Version])                 $("#Algorithm2").val(Algorithm);
   if(Level in JECData[Version][Algorithm])          $("#Level2").val(Level);
   if(Curve in JECData[Version][Algorithm][Level])   $("#Curve2").val(Curve);
   
   Version = "Autumn18_RunA_V8_DATA";
   Algorithm = "AK4PFchs";
   Level = "L1L2L3";
   Curve = "Eta_Rho40.00_PT100.00";

   if(Version in JECData)                            $("#Version3").val(Version);
   if(Algorithm in JECData[Version])                 $("#Algorithm3").val(Algorithm);
   if(Level in JECData[Version][Algorithm])          $("#Level3").val(Level);
   if(Curve in JECData[Version][Algorithm][Level])   $("#Curve3").val(Curve);
}

function UpdateHash()
{
   var HashString = "";

   var CurveCount = $('#CurveCount').val();

   for(var i = 0; i < MaxCurveCount; i++)
   {
      if(CurveCount > i)
      {
         if(i != 0)
            HashString = HashString + "+";
         HashString = HashString
            + $('#Version'+(i+1)).val() + ","
            + $('#Algorithm'+(i+1)).val() + ","
            + $('#Level'+(i+1)).val() + ","
            + $('#Curve'+(i+1)).val() + ","
            + $('#HideBand'+(i+1)+':checked').length;
      }
   }

   HashString = HashString + "&" + "ForceLinear=" + $('#ForceLinear:checked').length;

   window.location.hash = HashString;
}

function LoadFromHash()
{
   var HashString = window.location.hash;
   HashString = HashString.replace(/^#/, "");

   if(HashString == "")
   {
      LoadDefaultSetup();
      return;
   }

   var Curves = HashString.split('&')[0].split("+");
   var ExtraInformation = HashString.split('&');
   ExtraInformation.shift();

   // console.log("HashLoad split");
   // console.log(Curves);

   CurveCount = Curves.length;
   if(CurveCount > MaxCurveCount)
      CurveCount = MaxCurveCount;
   $('#CurveCount').val(CurveCount);

   var Version, Algorithm, Level, Curve, HideBand;

   var Error = false;

   for(var i = 0; i < MaxCurveCount; i++)
   {
      if(CurveCount <= i)
         continue;
      
      var Split = Curves[i].split(',');
      Version   = Split[0];
      Algorithm = Split[1];
      Level     = Split[2];
      Curve     = Split[3];
      if(Split.length > 4 && Split[4] == '0')
         HideBand = false;
      else
         HideBand = true;

      if(Version in JECData)
      {
         $("#Version"+(i+1)).val(Version);
         VersionChange($('#Version'+(i+1)), $('#Algorithm'+(i+1)), $('#Level'+(i+1)), $('#Curve'+(i+1)));
      }
      else
         Error = true;

      // console.log("HashLoad " + Version);
      // console.log("HashLoad " + Error);
      
      if(Error == false && (Algorithm in JECData[Version]))
      {
         $("#Algorithm"+(i+1)).val(Algorithm);
         AlgorithmChange($('#Version'+(i+1)), $('#Algorithm'+(i+1)), $('#Level'+(i+1)), $('#Curve'+(i+1)));
      }
      else
         Error = true;
      
      // console.log("HashLoad " + Algorithm);
      // console.log("HashLoad " + Error);
      
      if(Error == false && (Level in JECData[Version][Algorithm]))
      {
         $("#Level"+(i+1)).val(Level);
         LevelChange($('#Version'+(i+1)), $('#Algorithm'+(i+1)), $('#Level'+(i+1)), $('#Curve'+(i+1)));
      }
      else
         Error = true;
      
      // console.log("HashLoad " + Level);
      // console.log("HashLoad " + Error);
      
      if(Error == false && (Curve in JECData[Version][Algorithm][Level]))
      {
         $("#Curve"+(i+1)).val(Curve);
         CurveChange($('#Version'+(i+1)), $('#Algorithm'+(i+1)), $('#Level'+(i+1)), $('#Curve'+(i+1)));
      }
      else
         Error = true;
      
      // console.log("HashLoad " + Curve);
      // console.log("HashLoad " + Error);

      $('#HideBand'+(i+1)).prop('checked', HideBand);
   }

   for(var i = 0; i < ExtraInformation.length; i++)
   {
      if(ExtraInformation[i] == "ForceLinear=0")
         $('#ForceLinear').prop("checked", false);
      if(ExtraInformation[i] == "ForceLinear=1")
         $('#ForceLinear').prop("checked", true);
   }

   if(Error == true)
      LoadDefaultSetup();
}

function Initialize()
{
   for(var i = 0; i < MaxCurveCount; i++)  
   {
      SetListOfVersions($('#Version'+(i+1)));
      SetListOfAlgorithms($('#Version'+(i+1)), $('#Algorithm'+(i+1)));
      SetListOfLevels($('#Version'+(i+1)), $('#Algorithm'+(i+1)), $('#Level'+(i+1)));
      SetListOfCurves($('#Version'+(i+1)), $('#Algorithm'+(i+1)), $('#Level'+(i+1)), $('#Curve'+(i+1)));
   }

   LoadFromHash();

   // console.log('Initialize: ' + $('#Curve1').val());

   for(var i = 0; i < MaxCurveCount; i++)
      VersionChange($('#Version'+(i+1)), $('#Algorithm'+(i+1)), $('#Level'+(i+1)), $('#Curve'+(i+1)));
   
   UpdateGraph();
   UpdateHash();
   ShowHideSelector();

   for(var i = 0; i < MaxCurveCount; i++)
      $('div#color'+(i+1)).css('background-color', DefaultColors[i]);

   $('#CurveCount').change(function(){ShowHideSelector(); UpdateGraph(); UpdateHash();});

   $('#Version1').change(function(){VersionChange($('#Version1'), $('#Algorithm1'), $('#Level1'), $('#Curve1')); UpdateGraph(); UpdateHash();});
   $('#Version2').change(function(){VersionChange($('#Version2'), $('#Algorithm2'), $('#Level2'), $('#Curve2')); UpdateGraph(); UpdateHash();});
   $('#Version3').change(function(){VersionChange($('#Version3'), $('#Algorithm3'), $('#Level3'), $('#Curve3')); UpdateGraph(); UpdateHash();});
   $('#Version4').change(function(){VersionChange($('#Version4'), $('#Algorithm4'), $('#Level4'), $('#Curve4')); UpdateGraph(); UpdateHash();});
   $('#Version5').change(function(){VersionChange($('#Version5'), $('#Algorithm5'), $('#Level5'), $('#Curve5')); UpdateGraph(); UpdateHash();});
   $('#Version6').change(function(){VersionChange($('#Version6'), $('#Algorithm6'), $('#Level6'), $('#Curve6')); UpdateGraph(); UpdateHash();});
   
   $('#Algorithm1').change(function(){AlgorithmChange($('#Version1'), $('#Algorithm1'), $('#Level1'), $('#Curve1')); UpdateGraph(); UpdateHash();});
   $('#Algorithm2').change(function(){AlgorithmChange($('#Version2'), $('#Algorithm2'), $('#Level2'), $('#Curve2')); UpdateGraph(); UpdateHash();});
   $('#Algorithm3').change(function(){AlgorithmChange($('#Version3'), $('#Algorithm3'), $('#Level3'), $('#Curve3')); UpdateGraph(); UpdateHash();});
   $('#Algorithm4').change(function(){AlgorithmChange($('#Version4'), $('#Algorithm4'), $('#Level4'), $('#Curve4')); UpdateGraph(); UpdateHash();});
   $('#Algorithm5').change(function(){AlgorithmChange($('#Version5'), $('#Algorithm5'), $('#Level5'), $('#Curve5')); UpdateGraph(); UpdateHash();});
   $('#Algorithm6').change(function(){AlgorithmChange($('#Version6'), $('#Algorithm6'), $('#Level6'), $('#Curve6')); UpdateGraph(); UpdateHash();});
   
   $('#Level1').change(function(){LevelChange($('#Version1'), $('#Algorithm1'), $('#Level1'), $('#Curve1')); UpdateGraph(); UpdateHash();});
   $('#Level2').change(function(){LevelChange($('#Version2'), $('#Algorithm2'), $('#Level2'), $('#Curve2')); UpdateGraph(); UpdateHash();});
   $('#Level3').change(function(){LevelChange($('#Version3'), $('#Algorithm3'), $('#Level3'), $('#Curve3')); UpdateGraph(); UpdateHash();});
   $('#Level4').change(function(){LevelChange($('#Version4'), $('#Algorithm4'), $('#Level4'), $('#Curve4')); UpdateGraph(); UpdateHash();});
   $('#Level5').change(function(){LevelChange($('#Version5'), $('#Algorithm5'), $('#Level5'), $('#Curve5')); UpdateGraph(); UpdateHash();});
   $('#Level6').change(function(){LevelChange($('#Version6'), $('#Algorithm6'), $('#Level6'), $('#Curve6')); UpdateGraph(); UpdateHash();});
                                                            
   $('#Curve1').change(function(){CurveChange($('#Version1'), $('#Algorithm1'), $('#Level1'), $('#Curve1')); UpdateGraph(); UpdateHash();});
   $('#Curve2').change(function(){CurveChange($('#Version2'), $('#Algorithm2'), $('#Level2'), $('#Curve2')); UpdateGraph(); UpdateHash();});
   $('#Curve3').change(function(){CurveChange($('#Version3'), $('#Algorithm3'), $('#Level3'), $('#Curve3')); UpdateGraph(); UpdateHash();});
   $('#Curve4').change(function(){CurveChange($('#Version4'), $('#Algorithm4'), $('#Level4'), $('#Curve4')); UpdateGraph(); UpdateHash();});
   $('#Curve5').change(function(){CurveChange($('#Version5'), $('#Algorithm5'), $('#Level5'), $('#Curve5')); UpdateGraph(); UpdateHash();});
   $('#Curve6').change(function(){CurveChange($('#Version6'), $('#Algorithm6'), $('#Level6'), $('#Curve6')); UpdateGraph(); UpdateHash();});

   $('#HideBand1').change(function(){UpdateGraph(); UpdateHash();});
   $('#HideBand2').change(function(){UpdateGraph(); UpdateHash();});
   $('#HideBand3').change(function(){UpdateGraph(); UpdateHash();});
   $('#HideBand4').change(function(){UpdateGraph(); UpdateHash();});
   $('#HideBand5').change(function(){UpdateGraph(); UpdateHash();});
   $('#HideBand6').change(function(){UpdateGraph(); UpdateHash();});
   
   $('#ForceLinear').change(function(){UpdateGraph(); UpdateHash();});

   $('#Save').click(function()
   {
      // I think default is 96 dpi?
      var Width = $('#ChartDiv').width() / 96.0;
      var Height = $('#ChartDiv').height() / 96.0;
      var PdfFile = new jsPDF({orientation: 'landscape', unit: 'in', format: [Width, Height], compressPdf: true});
      PdfFile.addImage({imageData: Chart.getImageURI(), x: 0, y: 0, compression: 'SLOW'});
      PdfFile.save('JECChart.pdf');
   });
}

$(window).on('load', Initialize);

