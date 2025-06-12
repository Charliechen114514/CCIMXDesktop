#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H
class CVImage;
/**
 * @namespace FaceDetector
 */
namespace FaceDetector {
/**
 * @brief detectFaces
 * 
 * @param blank containers
 * @param src src
 */
void detectFaces(CVImage& blank, const CVImage& src);
};

#endif // FACEDETECTOR_H
