

int[][] arr = {};

int index = 0;
PImage bg;

PrintWriter output;

String[] lines;

void setup() {
  size(720, 1280);
  
  //output = createWriter("output.txt");
  //bg = loadImage("C:/Users/dorin/Documents/SensitiveData/mobility/for_processing.jpg");
  //background(bg);
  
  background(0);
  lines = loadStrings("output.txt");
}

void draw() {
  noStroke();
  
  String line = lines[index];
  int[] numbers = extractNumbers(line);
  
  circle(numbers[0], numbers[1], 5);
  if (index < lines.length-1) {
    index++;
  } else {
    output.close();
    noLoop();
    print("Finish");
  }
  saveFrame("line-######.png");
  
  if (mousePressed) {
    output.println("{" + mouseX + ", " + mouseY + "},");
    output.flush();
    //println("{" + mouseX + ", " + mouseY + "},");
  }
  
}

int[] extractNumbers(String line) {
  // Remove the curly braces and spaces
  line = line.replaceAll("[\\{\\}\\s]", "");
  
  // Split the line by the comma
  String[] parts = line.split(",");
  
  // Check if we have exactly two parts
  if (parts.length == 2) {
    try {
      // Parse the integers
      int num1 = int(parts[0]);
      int num2 = int(parts[1]);
      
      // Return the integers in an array
      return new int[] { num1, num2 };
    } catch (NumberFormatException e) {
      println("Number format exception: " + e.getMessage());
      return null;
    }
  } else {
    println("Invalid line format.");
    return null;
  }
}
