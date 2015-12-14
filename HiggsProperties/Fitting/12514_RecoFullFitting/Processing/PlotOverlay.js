var FadeTime = 400;
var VersionString = '';
var NewVersionString = "";
var CheckVersionLock = false;
var BaseURL = '';

$(document).ready(function()
{
   $('#LeftSample').buttonset();
   $('#LeftFloatAs').buttonset();
   $('#LeftFloatOthers').buttonset();
   $('#LeftSampleSize').buttonset();
   $('#LeftVariable').buttonset();
   $('#RightSample').buttonset();
   $('#RightFloatAs').buttonset();
   $('#RightFloatOthers').buttonset();
   $('#RightSampleSize').buttonset();
   $('#RightVariable').buttonset();

   $('#UpdateBox').hide();

   $(document).tooltip(
   {
      position:
      {
         my: "center bottom-20",
         at: "center top",
         using: function(position, feedback)
         {
            $(this).css(position);
            $("<div>").addClass("arrow")
               .addClass(feedback.vertical).addClass(feedback.horizontal).appendTo(this);
         }
      }
   });

   BaseURL = 'http://' + window.location.hostname + window.location.pathname;
   BaseURL = BaseURL.replace('index.html', '').replace('index_dev.html', '');

   $('#QueryLeft').change(function() {ChangePlot($(this), "#LeftPlot", "LeftSample", "#LeftLink");});
   $('#QueryRight').change(function() {ChangePlot($(this), "#RightPlot", "RightSample", "#RightLink");});

   $('#LeftSample, #LeftFloatAs, #LeftFloatOthers, #LeftSampleSize, #LeftVariable')
      .click(function() {window.setTimeout(ChangePlot('#LeftPlot', '#LeftLink', 'Left'), 0);});
   $('#RightSample, #RightFloatAs, #RightFloatOthers, #RightSampleSize, #RightVariable')
      .click(function() {window.setTimeout(ChangePlot('#RightPlot', '#RightLink', 'Right'), 0);});

   $('#LeftSample').click(function()
   {
      if($('input:radio[name=LeftSampleRadio]:checked').val() == 'Reco')
         EnableNNFChoiceLeft();
      if($('input:radio[name=LeftSampleRadio]:checked').val() == 'Gen')
         DisableNNFChoiceLeft();
   });

   $('#RightSample').click(function()
   {
      if($('input:radio[name=RightSampleRadio]:checked').val() == 'Reco')
         EnableNNFChoiceRight();
      if($('input:radio[name=RightSampleRadio]:checked').val() == 'Gen')
         DisableNNFChoiceRight();
   });

   $('#ModelSelector').click(function()
   {
      if($(this).html() === 'SM')
         $(this).html('Exotic');
      else
         $(this).html('SM');

      if($(this).html() === 'Exotic')
      {
         DisableGenLevelChoiceLeft();
         DisableGenLevelChoiceRight();
         if($('input:radio[name=LeftSampleRadio]:checked').val() == 'Reco')
            EnableNNFChoiceLeft();
         if($('input:radio[name=RightSampleRadio]:checked').val() == 'Reco')
            EnableNNFChoiceRight();
      }
      else
      {
         EnableGenLevelChoiceLeft();
         EnableGenLevelChoiceRight();
         if($('input:radio[name=LeftSampleRadio]:checked').val() == 'Reco')
            EnableNNFChoiceLeft();
         if($('input:radio[name=RightSampleRadio]:checked').val() == 'Reco')
            EnableNNFChoiceRight();
      }

      ChangePlot('#LeftPlot', '#LeftLink', 'Left');
      ChangePlot('#RightPlot', '#RightLink', 'Right');
   });

   $(".BigPlot").hover(function()
   {
      console.log('Mouse in!');
      
      $('#Overlay1').attr('src', $('#LeftPlot').attr('src'));
      $('#Overlay2').attr('src', $('#RightPlot').attr('src'));

      if(UrlExists($('#LeftPlot').attr('src')) == true)
         $('#Overlay1').stop().fadeTo(FadeTime, 1);
      if(UrlExists($('#RightPlot').attr('src')) == true)
         $('#Overlay2').stop().fadeTo(FadeTime, 1);
   },
   function()
   {
      console.log('Mouse out!');

      $('#Overlay1').stop().fadeOut(FadeTime);
      $('#Overlay2').stop().fadeOut(FadeTime);
   });

   // Now initialize things if there is a hash tag present
   if(window.location.hash !== '#' && window.location.hash !== '')
   {
      var toplevelarray = window.location.hash.split('+');
      if(toplevelarray.length != 3)
         return;

      console.log(toplevelarray);

      if(toplevelarray[0] == '#SM')
         $('#ModelSelector').html('SM');
      else
         $('#ModelSelector').html('Exotic');

      if($('#ModelSelector').html() === 'Exotic')
      {
         DisableGenLevelChoiceLeft();
         DisableGenLevelChoiceRight();
         if($('input:radio[name=LeftSampleRadio]:checked').val() == 'Reco')
            EnableNNFChoiceLeft();
         if($('input:radio[name=RightSampleRadio]:checked').val() == 'Reco')
            EnableNNFChoiceRight();
      }
      else
      {
         EnableGenLevelChoiceLeft();
         EnableGenLevelChoiceRight();
         if($('input:radio[name=LeftSampleRadio]:checked').val() == 'Reco')
            EnableNNFChoiceLeft();
         if($('input:radio[name=RightSampleRadio]:checked').val() == 'Reco')
            EnableNNFChoiceRight();
      }

      StringToPlotSelection(toplevelarray[1], 'Left');
      StringToPlotSelection(toplevelarray[2], 'Right');

      ChangePlot('#LeftPlot', '#LeftLink', 'Left');
      ChangePlot('#RightPlot', '#RightLink', 'Right');
   }
});

function DisableGenLevelChoiceLeft()
{
   $('#LeftSampleGen').removeAttr('checked').button('disable').button('refresh');
   $('#LeftSampleReco')[0].checked = true;
   $('#LeftSampleReco').button('refresh');
}

function DisableGenLevelChoiceRight()
{
   $('#RightSampleGen').removeAttr('checked').button('disable').button('refresh');
   $('#RightSampleReco')[0].checked = true;
   $('#RightSampleReco').button('refresh');
}

function DisableNNFChoice(prefix)
{
   if(prefix.toLowerCase() == 'left')
      DisableNNFChoiceLeft();
   else
      DisableNNFChoiceRight();
}

function DisableNNFChoiceLeft()
{
   $('#LeftN1CheckBox').removeAttr('checked').button('disable').button('refresh');
   $('#LeftN2CheckBox').removeAttr('checked').button('disable').button('refresh');
   $('#LeftBackgroundCheckBox').removeAttr('checked').button('disable').button('refresh');
   if($('input:radio[name=LeftVariable]:checked').val() == 'Fraction')
   {
      $('#LeftA2ZZVariable')[0].checked = true;
      $('#LeftA2ZZVariable').button('refresh');
      $('#LeftFemVariable').removeAttr('checked').button('disable').button('refresh');
   }
}

function DisableNNFChoiceRight()
{
   $('#RightN1CheckBox').removeAttr('checked').button('disable').button('refresh');
   $('#RightN2CheckBox').removeAttr('checked').button('disable').button('refresh');
   $('#RightBackgroundCheckBox').removeAttr('checked').button('disable').button('refresh');

   if($('input:radio[name=RightVariable]:checked').val() == 'Fraction')
   {
      $('#RightA2ZZVariable')[0].checked = true;
      $('#RightA2ZZVariable').button('refresh');
      $('#RightFemVariable').removeAttr('checked').button('disable').button('refresh');
   }
}

function EnableGenLevelChoiceLeft()
{
   $('#LeftSampleGen').button('enable').button('refresh');
}

function EnableGenLevelChoiceRight()
{
   $('#RightSampleGen').button('enable').button('refresh');
}

function EnableNNFChoice(prefix)
{
   if(prefix.toLowerCase() == 'left')
      EnableNNFChoiceLeft();
   else
      EnableNNFChoiceRight();
}

function EnableNNFChoiceLeft()
{
   $('#LeftN1CheckBox').button('enable').button('refresh');
   $('#LeftN2CheckBox').button('enable').button('refresh');
   $('#LeftBackgroundCheckBox').button('enable').button('refresh');
   $('#LeftFemVariable').button('enable').button('refresh');
}

function EnableNNFChoiceRight()
{
   $('#RightN1CheckBox').button('enable').button('refresh');
   $('#RightN2CheckBox').button('enable').button('refresh');
   $('#RightBackgroundCheckBox').button('enable').button('refresh');
   $('#RightFemVariable').button('enable').button('refresh');
}

function UrlExists(url)
{
   if(document.URL.search('localhost') >= 0 || document.URL.search('127.0.0.1') >= 0)
      return true;

   var http = new XMLHttpRequest();
   http.open('HEAD', url, false);
   http.send();
   return http.status != 404;
}

function CheckVersion()
{
   if(CheckVersionLock == true)
      return;
   CheckVersionLock = true;

   var http = new XMLHttpRequest();
   http.open("POST", BaseURL + "/VersionString", false);
   http.send();
   console.log(http.responseText);

   NewVersionString = http.responseText;
   if(NewVersionString === "")   // didn't get anything
   {
      CheckVersionLock = false;
      return;
   }

   if(VersionString === "")   // initializing
   {
      VersionString = NewVersionString;
      CheckVersionLock = false;
      return;
   }

   if(VersionString != NewVersionString)   // update is in place!
   {
      $('#UpdateBox').fadeTo(500, 1);
   }
   
   CheckVersionLock = false;
}

function ChangePlot(plotid, linkid, prefix)
{
   var SampleRadioName = prefix + 'SampleRadio';
   
   var SelectedSample = $('input:radio[name=' + SampleRadioName + ']:checked').val();
   var SelectedModel = $('#ModelSelector').html();
   
   var PlotDir = "/Plots/";

   if(SelectedModel === "SM" && SelectedSample === "Gen")        PlotDir = "/GenPlots/";
   if(SelectedModel === "SM" && SelectedSample === "MG")         PlotDir = "/MGPlots/";
   if(SelectedModel === "SM" && SelectedSample === "Reco")       PlotDir = "/Plots/";
   if(SelectedModel === "Exotic" && SelectedSample === "Gen")    PlotDir = "/ExoticGenPlots/";
   if(SelectedModel === "Exotic" && SelectedSample === "MG")     PlotDir = "/ExoticMGPlots/";
   if(SelectedModel === "Exotic" && SelectedSample === "Reco")   PlotDir = "/ExoticPlots/";
   console.log(PlotDir);

   var PlotIdentifier = PlotSelectionToString(prefix);

   var ProposedPlot = BaseURL + PlotDir + PlotIdentifier + '.gif';
   var ProposedLink = BaseURL + PlotDir + PlotIdentifier + '.pdf';
   var Exists = true;
   
   Exists = UrlExists(ProposedPlot) && UrlExists(ProposedLink);

   if(Exists == true && ProposedPlot != $(plotid).attr('src'))
   {
      $(plotid).stop().fadeTo(FadeTime, 0).fadeTo(FadeTime, 1);
      window.setTimeout(function()
      {
         $(plotid).attr('src', ProposedPlot);
         $(linkid).attr('href', ProposedLink);
      }, FadeTime);
   }
   else if(Exists == false)
   {
      $(plotid).stop().fadeOut(FadeTime);
      window.setTimeout(function()
      {
         $(plotid).attr('src', '');
         $(linkid).attr('href', '#');
      }, FadeTime);
   }

   document.location.hash = CurrentSelectionToHashString();

   window.setTimeout(CheckVersion(), 0);
}

function CurrentSelectionToHashString()
{
   var SelectedModel = $('#ModelSelector').html();
   if(SelectedModel == 'SM')
      FinalString = '#SM';
   else
      FinalString = '#Exotic';

   var LeftString = PlotSelectionToString('Left');
   var RightString = PlotSelectionToString('Right');
   
   LeftString = $('input:radio[name=LeftSampleRadio]:checked').val() + '_' + LeftString;
   RightString = $('input:radio[name=RightSampleRadio]:checked').val() + '_' + RightString;

   FinalString = FinalString + '+' + LeftString + '+' + RightString;

   return FinalString;
}

function PlotSelectionToString(prefix)
{
   var SampleRadioName = prefix + 'SampleRadio';
   var FloatA2ZZName = '#' + prefix + 'A2ZZCheckBox';
   var FloatA3ZZName = '#' + prefix + 'A3ZZCheckBox';
   var FloatA2ZAName = '#' + prefix + 'A2ZACheckBox';
   var FloatA3ZAName = '#' + prefix + 'A3ZACheckBox';
   var FloatA2AAName = '#' + prefix + 'A2AACheckBox';
   var FloatA3AAName = '#' + prefix + 'A3AACheckBox';
   var FloatN1Name = '#' + prefix + 'N1CheckBox';
   var FloatN2Name = '#' + prefix + 'N2CheckBox';
   var FloatBackgroundName = '#' + prefix + 'BackgroundCheckBox';
   var SampleSizeRadioName = prefix + 'SampleSizeRadio';
   var VariableRadioName = prefix + 'VariableRadio';

   var SelectedSample = $('input:radio[name=' + SampleRadioName + ']:checked').val();

   var PlotIdentifier = 'H_';
   if($(FloatA2ZZName).is(':checked') == true)   PlotIdentifier = PlotIdentifier + 'Y';
   else                                          PlotIdentifier = PlotIdentifier + 'N';
   if($(FloatA3ZZName).is(':checked') == true)   PlotIdentifier = PlotIdentifier + 'Y';
   else                                          PlotIdentifier = PlotIdentifier + 'N';
   if($(FloatA2ZAName).is(':checked') == true)   PlotIdentifier = PlotIdentifier + 'Y';
   else                                          PlotIdentifier = PlotIdentifier + 'N';
   if($(FloatA3ZAName).is(':checked') == true)   PlotIdentifier = PlotIdentifier + 'Y';
   else                                          PlotIdentifier = PlotIdentifier + 'N';
   if($(FloatA2AAName).is(':checked') == true)   PlotIdentifier = PlotIdentifier + 'Y';
   else                                          PlotIdentifier = PlotIdentifier + 'N';
   if($(FloatA3AAName).is(':checked') == true)   PlotIdentifier = PlotIdentifier + 'Y';
   else                                          PlotIdentifier = PlotIdentifier + 'N';

   PlotIdentifier = PlotIdentifier + '_';
   if($(FloatN1Name).is(':checked') == true)   PlotIdentifier = PlotIdentifier + 'Y';
   else                                        PlotIdentifier = PlotIdentifier + 'N';
   if($(FloatN2Name).is(':checked') == true)   PlotIdentifier = PlotIdentifier + 'Y';
   else                                        PlotIdentifier = PlotIdentifier + 'N';
   
   PlotIdentifier = PlotIdentifier + '_';
   if($(FloatBackgroundName).is(':checked') == true)   PlotIdentifier = PlotIdentifier + 'Y';
   else                                                PlotIdentifier = PlotIdentifier + 'N';

   PlotIdentifier = PlotIdentifier + '_' + $('input:radio[name=' + SampleSizeRadioName + ']:checked').val();

   PlotIdentifier = PlotIdentifier + '_' + $('input:radio[name=' + VariableRadioName + ']:checked').val();

   // console.log(PlotIdentifier);

   return PlotIdentifier;
}

function StringToPlotSelection(string, prefix)
{
   var IdentifierArray = string.split('_');
   console.log(IdentifierArray);
   if(IdentifierArray.length != 7)
      return;

   if(IdentifierArray[0].toLowerCase() == 'mg' && $('#' + prefix + 'SampleMG').is(':enabled'))
      $('#' + prefix + 'SampleMG')[0].checked = true;
   if(IdentifierArray[0].toLowerCase() == 'gen' && $('#' + prefix + 'SampleGen').is(':enabled'))
      $('#' + prefix + 'SampleGen')[0].checked = true;
   if(IdentifierArray[0].toLowerCase() == 'reco' && $('#' + prefix + 'SampleReco').is(':enabled'))
      $('#' + prefix + 'SampleReco')[0].checked = true;

   $('#' + prefix + 'SampleMG').button('refresh');
   $('#' + prefix + 'SampleGen').button('refresh');
   $('#' + prefix + 'SampleReco').button('refresh');

   if($('#' + prefix + 'SampleMG').is(':checked'))
      DisableNNFChoice(prefix);
   if($('#' + prefix + 'SampleGen').is(':checked'))
      DisableNNFChoice(prefix);
   if($('#' + prefix + 'SampleReco').is(':checked'))
      EnableNNFChoice(prefix);

   if(IdentifierArray[2].charAt(0) == 'N')
      $('#' + prefix + 'A2ZZCheckBox').attr('checked', false);
   if(IdentifierArray[2].charAt(0) == 'Y' && $('#' + prefix + 'A2ZZCheckBox').is(':enabled'))
      $('#' + prefix + 'A2ZZCheckBox').attr('checked', true);
   if(IdentifierArray[2].charAt(1) == 'N')
      $('#' + prefix + 'A3ZZCheckBox').attr('checked', false);
   if(IdentifierArray[2].charAt(1) == 'Y' && $('#' + prefix + 'A3ZZCheckBox').is(':enabled'))
      $('#' + prefix + 'A3ZZCheckBox').attr('checked', true);
   if(IdentifierArray[2].charAt(2) == 'N')
      $('#' + prefix + 'A2ZACheckBox').attr('checked', false);
   if(IdentifierArray[2].charAt(2) == 'Y' && $('#' + prefix + 'A2ZACheckBox').is(':enabled'))
      $('#' + prefix + 'A2ZACheckBox').attr('checked', true);
   if(IdentifierArray[2].charAt(3) == 'N')
      $('#' + prefix + 'A3ZACheckBox').attr('checked', false);
   if(IdentifierArray[2].charAt(3) == 'Y' && $('#' + prefix + 'A3ZACheckBox').is(':enabled'))
      $('#' + prefix + 'A3ZACheckBox').attr('checked', true);
   if(IdentifierArray[2].charAt(4) == 'N')
      $('#' + prefix + 'A2AACheckBox').attr('checked', false);
   if(IdentifierArray[2].charAt(4) == 'Y' && $('#' + prefix + 'A2AACheckBox').is(':enabled'))
      $('#' + prefix + 'A2AACheckBox').attr('checked', true);
   if(IdentifierArray[2].charAt(5) == 'N')
      $('#' + prefix + 'A3AACheckBox').attr('checked', false);
   if(IdentifierArray[2].charAt(5) == 'Y' && $('#' + prefix + 'A3AACheckBox').is(':enabled'))
      $('#' + prefix + 'A3AACheckBox').attr('checked', true);

   $('#' + prefix + 'A2ZZCheckBox').button('refresh');
   $('#' + prefix + 'A3ZZCheckBox').button('refresh');
   $('#' + prefix + 'A2ZACheckBox').button('refresh');
   $('#' + prefix + 'A3ZACheckBox').button('refresh');
   $('#' + prefix + 'A2AACheckBox').button('refresh');
   $('#' + prefix + 'A3AACheckBox').button('refresh');

   if(IdentifierArray[3].charAt(0) == 'N')
      $('#' + prefix + 'N1CheckBox').attr('checked', false);
   if(IdentifierArray[3].charAt(0) == 'Y' && $('#' + prefix + 'N1CheckBox').is(':enabled'))
      $('#' + prefix + 'N1CheckBox').attr('checked', true);
   if(IdentifierArray[3].charAt(1) == 'N')
      $('#' + prefix + 'N2CheckBox').attr('checked', false);
   if(IdentifierArray[3].charAt(1) == 'Y' && $('#' + prefix + 'N2CheckBox').is(':enabled'))
      $('#' + prefix + 'N2CheckBox').attr('checked', true);
   
   $('#' + prefix + 'N1CheckBox').button('refresh');
   $('#' + prefix + 'N2CheckBox').button('refresh');

   if(IdentifierArray[4].charAt(0) == 'N')
      $('#' + prefix + 'BackgroundCheckBox').attr('checked', false);
   if(IdentifierArray[4].charAt(0) == 'Y' && $('#' + prefix + 'BackgroundCheckBox').is(':enabled'))
      $('#' + prefix + 'BackgroundCheckBox').attr('checked', true);
   
   $('#' + prefix + 'BackgroundCheckBox').button('refresh');
   
   if(IdentifierArray[5].charAt(0) == '1' && $('#' + prefix + 'Sample1Radio').is(':enabled'))
      $('#' + prefix + 'Sample1Radio').attr('checked', true);
   if(IdentifierArray[5].charAt(0) == '2' && $('#' + prefix + 'Sample2Radio').is(':enabled'))
      $('#' + prefix + 'Sample2Radio').attr('checked', true);
   if(IdentifierArray[5].charAt(0) == '3' && $('#' + prefix + 'Sample3Radio').is(':enabled'))
      $('#' + prefix + 'Sample3Radio').attr('checked', true);
   if(IdentifierArray[5].charAt(0) == '4' && $('#' + prefix + 'Sample4Radio').is(':enabled'))
      $('#' + prefix + 'Sample4Radio').attr('checked', true);
   if(IdentifierArray[5].charAt(0) == '5' && $('#' + prefix + 'Sample5Radio').is(':enabled'))
      $('#' + prefix + 'Sample5Radio').attr('checked', true);
   if(IdentifierArray[5].charAt(0) == '6' && $('#' + prefix + 'Sample6Radio').is(':enabled'))
      $('#' + prefix + 'Sample6Radio').attr('checked', true);
   if(IdentifierArray[5].charAt(0) == '7' && $('#' + prefix + 'Sample7Radio').is(':enabled'))
      $('#' + prefix + 'Sample7Radio').attr('checked', true);

   $('#' + prefix + 'Sample1Radio').button('refresh');
   $('#' + prefix + 'Sample2Radio').button('refresh');
   $('#' + prefix + 'Sample3Radio').button('refresh');
   $('#' + prefix + 'Sample4Radio').button('refresh');
   $('#' + prefix + 'Sample5Radio').button('refresh');
   $('#' + prefix + 'Sample6Radio').button('refresh');
   $('#' + prefix + 'Sample7Radio').button('refresh');

   if(IdentifierArray[6] == 'A2ZZ' && $('#' + prefix + 'A2ZZVariable').is(':enabled'))
      $('#' + prefix + 'A2ZZVariable').attr('checked', true);
   if(IdentifierArray[6] == 'A3ZZ' && $('#' + prefix + 'A3ZZVariable').is(':enabled'))
      $('#' + prefix + 'A3ZZVariable').attr('checked', true);
   if(IdentifierArray[6] == 'A2ZA' && $('#' + prefix + 'A2ZAVariable').is(':enabled'))
      $('#' + prefix + 'A2ZAVariable').attr('checked', true);
   if(IdentifierArray[6] == 'A3ZA' && $('#' + prefix + 'A3ZAVariable').is(':enabled'))
      $('#' + prefix + 'A3ZAVariable').attr('checked', true);
   if(IdentifierArray[6] == 'A2AA' && $('#' + prefix + 'A2AAVariable').is(':enabled'))
      $('#' + prefix + 'A2AAVariable').attr('checked', true);
   if(IdentifierArray[6] == 'A3AA' && $('#' + prefix + 'A3AAVariable').is(':enabled'))
      $('#' + prefix + 'A3AAVariable').attr('checked', true);
   if(IdentifierArray[6] == 'Fraction' && $('#' + prefix + 'FemVariable').is(':enabled'))
      $('#' + prefix + 'FemVariable').attr('checked', true);
   
   $('#' + prefix + 'A2ZZVariable').button('refresh');
   $('#' + prefix + 'A3ZZVariable').button('refresh');
   $('#' + prefix + 'A2ZAVariable').button('refresh');
   $('#' + prefix + 'A3ZAVariable').button('refresh');
   $('#' + prefix + 'A2AAVariable').button('refresh');
   $('#' + prefix + 'A3AAVariable').button('refresh');
   $('#' + prefix + 'FemVariable').button('refresh');
}





