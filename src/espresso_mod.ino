const int singleShotButton = 2; // Pin connected to Single Shot button
const int doubleShotButton = 3; // Pin connected to Double Shot button
const int purgeShotButton = 4;  // Pin connected to Purge Shot button
const int stopButton = 5;       // Pin connected to Stop button
const int relayPin = 7;         // Pin connected to relay

const int ledPin = 13;

int singleShotTime = 12500; // Single shot brew time in milliseconds (12.5 seconds)
int doubleShotTime = 24500; // Double shot brew time in milliseconds (24.5 seconds)
int purgeShotTime = 3000;   // Purge shot time in milliseconds (3 seconds)

bool isBrewing = false;          // Variable to track if brewing is in progress
unsigned long brewStartTime = 0; // Variable to track brew start time
unsigned long brewDuration = 0;  // Variable to store the duration of the current brew

// Button states for debouncing
int singleShotButtonState = 0;
int lastSingleShotButtonState = 0;
unsigned long lastSingleShotDebounceTime = 0;

int doubleShotButtonState = 0;
int lastDoubleShotButtonState = 0;
unsigned long lastDoubleShotDebounceTime = 0;

int purgeShotButtonState = 0;
int lastPurgeShotButtonState = 0;
unsigned long lastPurgeShotDebounceTime = 0;

int stopButtonState = 0;
int lastStopButtonState = 0;
unsigned long lastStopDebounceTime = 0;

unsigned long debounceDelay = 50; // Debounce time in milliseconds

void setup()
{
    pinMode(singleShotButton, INPUT); // Set Single Shot button as input
    pinMode(doubleShotButton, INPUT); // Set Double Shot button as input
    pinMode(purgeShotButton, INPUT);  // Set Purge Shot button as input
    pinMode(stopButton, INPUT);       // Set Stop button as input (without pull-up)
    pinMode(relayPin, OUTPUT);        // Set relay pin as output
    pinMode(ledPin, OUTPUT);

    digitalWrite(relayPin, HIGH); // Ensure relay is off initially
}

void loop()
{
    // Read button states
    int singleShotReading = digitalRead(singleShotButton);
    int doubleShotReading = digitalRead(doubleShotButton);
    int purgeShotReading = digitalRead(purgeShotButton);
    int stopReading = digitalRead(stopButton); // Stop button reading

    // Check if stop button is pressed
    if (stopReading != lastStopButtonState)
    {
        lastStopDebounceTime = millis(); // Reset debounce timer
    }

    if ((millis() - lastStopDebounceTime) > debounceDelay)
    {
        if (stopReading != stopButtonState)
        {
            stopButtonState = stopReading;

            // Stop Button Pressed (button connected to 5V)
            if (stopButtonState == HIGH && isBrewing)
            {
                stopBrew(); // Stop the current brew cycle if brewing
            }
        }
    }

    lastStopButtonState = stopReading; // Save current state

    // If brewing is in progress, check the elapsed time
    if (isBrewing)
    {
        unsigned long currentTime = millis();
        if (currentTime - brewStartTime >= brewDuration)
        {
            stopBrew(); // Automatically stop brew when the set time has passed
        }
        return; // Exit loop to allow brewing to continue without checking other buttons
    }

    // Check for button presses and debounce logic
    // Single Shot Button
    if (singleShotReading != lastSingleShotButtonState)
    {
        lastSingleShotDebounceTime = millis(); // Reset debounce timer
    }

    if ((millis() - lastSingleShotDebounceTime) > debounceDelay)
    {
        if (singleShotReading != singleShotButtonState)
        {
            singleShotButtonState = singleShotReading;

            // Single Shot Button Pressed
            if (singleShotButtonState == HIGH && !isBrewing)
            {
                startBrew(singleShotTime);
            }
        }
    }

    lastSingleShotButtonState = singleShotReading; // Save the current state for the next loop

    // Double Shot Button
    if (doubleShotReading != lastDoubleShotButtonState)
    {
        lastDoubleShotDebounceTime = millis(); // Reset debounce timer
    }

    if ((millis() - lastDoubleShotDebounceTime) > debounceDelay)
    {
        if (doubleShotReading != doubleShotButtonState)
        {
            doubleShotButtonState = doubleShotReading;

            // Double Shot Button Pressed
            if (doubleShotButtonState == HIGH && !isBrewing)
            {
                startBrew(doubleShotTime);
            }
        }
    }

    lastDoubleShotButtonState = doubleShotReading; // Save the current state for the next loop

    // Purge Shot Button
    if (purgeShotReading != lastPurgeShotButtonState)
    {
        lastPurgeShotDebounceTime = millis(); // Reset debounce timer
    }

    if ((millis() - lastPurgeShotDebounceTime) > debounceDelay)
    {
        if (purgeShotReading != purgeShotButtonState)
        {
            purgeShotButtonState = purgeShotReading;

            // Purge Shot Button Pressed
            if (purgeShotButtonState == HIGH && !isBrewing)
            {
                startBrew(purgeShotTime);
            }
        }
    }

    lastPurgeShotButtonState = purgeShotReading; // Save the current state for the next loop
}

// Function to start brewing for the specified time
void startBrew(int brewTime)
{
    isBrewing = true;
    brewDuration = brewTime;
    brewStartTime = millis(); // Record the time the brew started
    digitalWrite(ledPin, HIGH);
    digitalWrite(relayPin, LOW); // Turn on relay (brew/purge starts)
}

// Function to stop the current brew or purge
void stopBrew()
{
    digitalWrite(ledPin, LOW);
    digitalWrite(relayPin, HIGH); // Turn off relay immediately
    isBrewing = false;            // Reset brewing state
}
