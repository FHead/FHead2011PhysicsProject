var DefaultColors = ['#A52714', '#097138', '#00FF00', '#FF0000', '#0000FF']

var DefaultOptions =
{
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
   legend: {position: 'top', maxLines: 3},
   chartArea: {width: '85%', height: '75%', left: '10%', top: '15%'},
   colors: DefaultColors,
   explorer:
   {
      actions: ['dragToZoom', 'rightClickToReset'],
      axis: 'horizontal',
      keepInBounds: true,
      maxZoomIn: 0.1,
      maxZoomOut: 1.0,
      zoomDelta: 1.05
   },
};

var MaxCurveCount = 5;


