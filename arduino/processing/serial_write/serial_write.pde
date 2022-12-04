float xloc;
float yloc;
float xprev;
float yprev;
import processing.serial.*;
Serial port;

void setup() {
  size(500,300);
  printArray(Serial.list());
  try{
    port = new Serial(this, Serial.list()[2], 9600);
  }
  catch(Exception e){
    System.err.println(e);
    e.printStackTrace();
  }
}

void draw() {
  xloc = mouseX;
  yloc = mouseY;
  port.write(str(mouseX)+' '+str(mouseY) + "\n");
  //text(mouseX,250,50);
  //text(mouseY,250,70);
  
  if(port.available() > 0){
    String in = port.readString();
    if (in != null && (xprev != xloc || yprev != yloc)) {
      println(in);
    }
  }
  xprev = xloc;
  yprev = yloc;
}
