import processing.serial.*;
import codeanticode.syphon.*;
    
Serial myPort;
PGraphics canvas;
SyphonServer server;

float rango = 5;
float xPos = rango; // horizontal position of the graph
float oldHeartrateHeight = 0; // for storing the previous reading
float x1 =0, x2 =0, y1 =0, y2=0;
    
void setup () {
  // set the window size:
  size(1280, 720, P3D);
  canvas = createGraphics(1280,720,P3D);
  frameRate(25);
  noSmooth();
    
  String portName =  Serial.list()[3];
  println(portName);
  myPort = new Serial(this, portName, 9600);

  server = new SyphonServer(this, "Processing Syphon");
  paintBg();
}

void paintBg() {
  canvas.beginDraw();
  canvas.background(0);
  canvas.endDraw();
  image(canvas, 0, 0);
  server.sendImage(canvas);
}

void draw () {
  canvas.beginDraw();
  if(y1 >700) {
    canvas.background(255, 0, 0);
   }
   else {
     canvas.background(0,0,0);
   }
  
  canvas.strokeWeight(3);
  canvas.line(x1, y1, x2, y2);
  canvas.endDraw();
  image(canvas, 0, 0);

  server.sendImage(canvas);
      
  if (xPos >= width) {
    xPos = 0;
    paintBg();
  } else {
    // increment the horizontal position:
    xPos+=rango;
  }
}

void serialEvent (Serial myPort) {
  // read the string from the serial port.
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
  // trim off any whitespace:
    inString = trim(inString);
    // convert to an int
    //println(inString);
    int currentHeartrate = int(inString);

    // draw the Heartrate BPM Graph.
    float heartrateHeight = map(currentHeartrate, 0, 255, 0, height);
    x1= xPos - rango;
    x2 = xPos;
    y1 = height - oldHeartrateHeight;
    y2 = height - heartrateHeight;
    
    println(x1, y1, x2, y2);
    oldHeartrateHeight = heartrateHeight;
    // at the edge of the screen, go back to the beginning:
    
   }
 }
