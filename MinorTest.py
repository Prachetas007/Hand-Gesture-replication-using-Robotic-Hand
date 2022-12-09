import cvzone
from serial import Serial
from cvzone.HandTrackingModule import HandDetector
from cvzone.SerialModule import SerialObject 
import cv2


cap = cv2.VideoCapture(0)
# Define the codec and create VideoWriter object.The output is stored in 'outpy.avi' file.
# out = cv2.VideoWriter('/home/prachetas/Desktop/MinorProject.avi',cv2.VideoWriter_fourcc('M','J','P','G'), 10, (20,20))
 
detector = HandDetector(detectionCon=0.5, maxHands=2)
mySerial = SerialObject("/dev/ttyACM0" , 9600, 1)
while True:
    success, img = cap.read()
    hands, img = detector.findHands(img)
   
    # if lmList:
    if hands:
        # Hand 1
        hand1 = hands[0]
        lmList1 = hand1["lmList"]  # List of 21 Landmark points
        bbox1 = hand1["bbox"]  # Bounding box info x,y,w,h
        centerPoint1 = hand1['center']  # center of the hand cx,cy
        handType1 = hand1["type"]  # Handtype Left or Right

        fingers1 = detector.fingersUp(hand1)
        print(fingers1)
        # out.write(img)

        string1 = ''.join(map(str,fingers1))
        string1 = '$' + string1
        mySerial.sendData(fingers1)
    # fingers = detector.fingersUp(hands)
    # print(fingers)
    cv2.imshow("Image" , img)
    
    if cv2.waitKey(5) & 0xFF == 27:
      break

# out.release()
cap.release()
cv2.destroyAllWindows()