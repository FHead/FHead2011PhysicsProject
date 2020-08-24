// var DefaultColors = ['#A52714', '#097138', '#00FF00', '#FF0000', '#0000FF', '#FF00FF', '#008888']
// Andreas May 14: wants black, red, blue, pink, yellow, green
var DefaultColors = ['#2C3E50', '#E74C3C', '#3498DB', '#8E44AD', '#F1C40F', '#2ECC71']
var DefaultWidth = 2;

var Scale = 1;

var DefaultOptions =
{
   interpolateNulls: true,
   hAxis:
   {
      title: 'X',
      textStyle: {color: '#01579b', fontSize: 16, fontName: 'Arial', italic: false},
      titleTextStyle: {color: '#01579b', fontSize: 16, fontName: 'Arial', italic: false }
   },
   vAxis:
   {
      title: 'Correction',
      textStyle: {color: '#1a237e', fontSize: 16, fontName: 'Arial', italic: false},
      titleTextStyle: {color: '#1a237e', fontSize: 16, fontName: 'Arial', italic: false}
   },
   legend: {position: 'top', maxLines: 3, textStyle: {fontSize: 16}},
   chartArea: {width: '85%', height: '75%', left: '10%', top: '15%'},
   explorer:
   {
      actions: ['dragToZoom', 'rightClickToReset'],
      // axis: 'horizontal',
      keepInBounds: true,
      maxZoomIn: 0.05,
      maxZoomOut: 1.0,
      zoomDelta: 1.05
   },
};

var MaxCurveCount = 6;


