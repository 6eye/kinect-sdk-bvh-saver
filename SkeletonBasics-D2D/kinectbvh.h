#ifndef KINECTBVH_H
#define KINECTBVH_H

#define SCALE 1.f
#define FPS 0.033333

#include <windows.h>
#include <NuiApi.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "vec_math.h"
#include "quat2euler.h"

using namespace std;

struct KinectJoint
{
	Vector4 quat;
};

/**
* Manipule les donn�es de la Kinect que la classe KinectSkeleton a envoy?et g�n�re le fichier BVH r�sultant de la capture de mouvements
*/
class KinectBVH
{
public:
	/**
	* Constructeur
	*/
	KinectBVH();
	/**
	* Destructeur
	*/
	~KinectBVH();

	/**
	* Ajoute un offset ?la description du BVH
	*/
	void AddOffset(int, const Vector4 &);
	/**
	* Ajoute un squelette et ses informations pour les donn�es de la capture de mouvements
	*/
	void AddBonesOrientation(KinectJoint *);
	/**
	* Ajoute une position du joint Hip Center pour les donn�es de la capture de mouvements
	*/
	void AddPosition(const Vector4 &);
	/**
	* Incr�mente le nombre de frames
	*/
	void IncrementNbFrames();
	/**
	* Cr�� un nouveau fichier en fonction du nom re�u en param�tre, renvoi true si r�ussi sinon false
	*/
	bool CreateBVHFile(string);
	/**
	* G�n�re le fichier BVH
	*/
	void FillBVHFile();
private:
	// Fichier
	ofstream m_pFile;

	// pre-calculated quaternions
	Vec_Math::Quaternion q_z_40;
	Vec_Math::Quaternion q_z_320;
	Vec_Math::Quaternion q_z_30;
	Vec_Math::Quaternion q_z_330;

	// Offsets
	vector<Vector4> m_aOffsets;
	// Positions du Hip Center
	vector<Vector4> m_vPositions;
	// Squelettes et leurs informations des joints
	vector<KinectJoint> m_vBonesOrientation;

	// Nombre de frames
	int m_nbFrame;

	void GetAngles(KinectJoint *, int, double []);

	/**
	* G�n�re la description du squelette pour le BVH
	*/
	void CreateSkeletonInformation();
	/**
	* G�n�re les donn�es des mouvements pour le BVH
	*/
	void CreateMotionInformation();
};

#endif // KINECTBVH_H
