/* Defines */

#define RUNDEPTH 	10.6
#define RUNSPEED	80.0
#define HACC		5.0
#define HCOUNT		10

/* state 0*/
#define FIRSTHEADING	225.0

/* state 1 */
#define OUTTIME		20

/* state 2 */
#define SECONDHEADING	85.0

/* state 3 */
#define INTIME		20

/* default */

#define	STOPSPEED	-10.0
#define	STOPHEADING	90.0
#define	STOPDEPTH	10.2

/* Globals*/

float heading=0.0;
float pitch=0.0;
float depth=0.0;

unsigned int switcher=0;
unsigned int tcounter=0;
unsigned int hcounter=0;

unsigned int go = 0;
unsigned int latch = 0;

/* Function Declerations */

void headingCallback(const std_msgs::Float32::ConstPtr& compassHeading);
void pitchCallback(const std_msgs::Float32::ConstPtr& compassPitch);
void depthCallback(const std_msgs::Float32::ConstPtr& svpDepth);
void adcGoCallback(const std_msgs::UInt32::ConstPtr& adcGo);
