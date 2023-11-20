function pose = MyreadPose(odomMsg)
poseMsg = odomMsg.Pose.Pose;
xpos = poseMsg.Position.X;
ypos = poseMsg.Position.Y;
quat = poseMsg.Orientation;
angles = quat2eul([quat.W quat.X quat.Y quat.Z]);
theta = angles(1);
pose = [xpos, ypos, theta];
end

