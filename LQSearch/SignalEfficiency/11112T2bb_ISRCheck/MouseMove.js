var MouseX = 0;
var MouseY = 0;
var XScreenMin = 52;
var XScreenMax = 459;
var YScreenMin = 437;
var YScreenMax = 51;
var XAxisMin = 0;
var XAxisMax = 1250;
var YAxisMin = 0;
var YAxisMax = 1250;
var XBinCount = 50;
var YBinCount = 50;

var IE = document.all ? true : false;
if(!IE)
   document.captureEvents(Event.MOUSEMOVE);

function GetMouseXY(event)
{
   if(IE)
   {
      MouseX = event.clientX + document.body.scrollLeft;
      MouseY = event.clientY + document.body.scrollTop;
   }
   else
   {
      MouseX = event.pageX;
      MouseY = event.pageY;
   }  

   if(MouseX < 0)
      MouseX = 0;
   if(MouseY < 0)
      MouseY = 0;
}

function MouseMove(event)
{
   GetMouseXY(event);

   // document.getElementById('DebugPanel').innerHTML = MouseX + ' ' + MouseY + '<br />';

   var BlockSizeX = (XAxisMax - XAxisMin) / XBinCount;
   var BlockSizeY = (YAxisMax - YAxisMin) / YBinCount;

   for(i = 0; i < OccupiedList.length; i++)
   {
      var XMin = OccupiedList[i].X;
      var YMin = OccupiedList[i].Y;

      var BlockXMin = (XMin - XAxisMin) / (XAxisMax - XAxisMin) * (XScreenMax - XScreenMin) + XScreenMin;
      var BlockXMax = (XMin + BlockSizeX - XAxisMin) / (XAxisMax - XAxisMin) * (XScreenMax - XScreenMin) + XScreenMin;
      var BlockYMin = (YMin - YAxisMin) / (YAxisMax - YAxisMin) * (YScreenMax - YScreenMin) + YScreenMin;
      var BlockYMax = (YMin + BlockSizeY - YAxisMin) / (YAxisMax - YAxisMin) * (YScreenMax - YScreenMin) + YScreenMin;

      // document.getElementById('DebugPanel').innerHTML += BlockXMin + ' ' + BlockXMax + ' '
      //    + BlockYMin + ' ' + BlockYMax + '<br />';
      // document.getElementById('DebugPanel').innerHTML += Math.min(BlockXMin, BlockXMax) + '<br />';
   
      if(MouseX > Math.min(BlockXMin, BlockXMax) && MouseX < Math.max(BlockXMin, BlockXMax)
         && MouseY > Math.min(BlockYMin, BlockYMax) && MouseY < Math.max(BlockYMin, BlockYMax))
      {
         document.getElementById('TopImage').src = 'Histograms/PT_' + OccupiedList[i].Identifier + ".png";
         document.getElementById('BottomImage').src = 'Histograms/Weight_' + OccupiedList[i].Identifier + ".png";

         // document.getElementById('DebugPanel').innerHTML += document.getElementById('TopImage').src + '<br />';
      }
   }
}









