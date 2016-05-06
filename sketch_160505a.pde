import processing.net.*; 
import processing.serial.*;

Serial arduino;  // Arduino sur le port Serie
Client gqrx; // commande gqrx en TCP/IP


void setup() {
  printArray(Serial.list());
  arduino = new Serial(this, Serial.list()[5], 9600); //réglage du port
}

void draw() {
  while (arduino.available() > 0) {
    String request = arduino.readString();  //lecture du port série
    delay(300); //attente pour une bonne reception
    if (request != null) {
      gqrx = new Client(this, "127.0.0.1", 7356); //connection au serveur
      gqrx.write(request); //envoie de la requette
      println(request); //affichage de la requette
    }
  }
}