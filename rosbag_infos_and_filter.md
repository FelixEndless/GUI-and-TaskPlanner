// Liste von Topics die gerade gepublisht werden
rostopic list -v

//aus aufgenommenen .bag-File lesen was es enthält
rosbag info <your .bag-File>

//rosbag abspielen
rosbag play <your .bag-File>

//Vorhandenes bag-File filtern und als neues .bag-File speichern
//http://wiki.ros.org/rosbag/Tutorials/Producing%20filtered%20bag%20files
rosbag filter <your .bag-File> <name des neuen .bag-Files> 'topic == "/turtle1/command_velocity"'

//so kann man beispielsweise auch bestimmte Bewegungen herausfiltern, z.B. Rechtsbewegungen
//zuletzt steht die Bedinung "m.angular >= 0", welche bedeutet, dass richtungsänderungen mit einem Winkel von nur noch >=0° zugelassen sind
rosbag filter <your .bag-File> <new .bag-File-Name> "m.angular >= 0"
