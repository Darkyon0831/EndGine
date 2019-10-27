#include  "Matrix.h"

const EG::Matrix& EG::Matrix::identity
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

EG::Matrix::Matrix
(
	float _11, float _12, float _13, float _14, 
	float _21, float _22, float _23, float _24, 
	float _31, float _32, float _33, float _34, 
	float _41, float _42, float _43, float _44
)
: m_11(_11), m_12(_12), m_13(_13), m_14(_14)
, m_21(_21), m_22(_22), m_23(_23), m_24(_24)
, m_31(_31), m_32(_32), m_33(_33), m_34(_34)
, m_41(_41), m_42(_42), m_43(_43), m_44(_44)
{
	
}

void EG::Matrix::RotateX(float angle, CombineFunc combine)
{
	Matrix rotationMatrixX = Matrix::identity;

	angle *= static_cast<float>(M_PI / 180.0f);
	
	rotationMatrixX[5] = cos(angle);
	rotationMatrixX[6] = -sin(angle);
	rotationMatrixX[9] = sin(angle);
	rotationMatrixX[10] = cos(angle);

	if (combine == CombineFunc::PreMultiply)
		*this = rotationMatrixX * *this;
	else if (combine == CombineFunc::PostMultiply)
		*this = *this * rotationMatrixX;
	else if (combine == CombineFunc::Replace)
		*this = rotationMatrixX;
}

void EG::Matrix::RotateY(float angle, CombineFunc combine)
{
	Matrix rotationMatrixY = Matrix::identity;

	angle *= static_cast<float>(M_PI / 180.0f);

	rotationMatrixY[0] = cos(angle);
	rotationMatrixY[2] = sin(angle);
	rotationMatrixY[8] = -sin(angle);
	rotationMatrixY[10] = cos(angle);

	if (combine == CombineFunc::PreMultiply)
		*this = rotationMatrixY * *this;
	else if (combine == CombineFunc::PostMultiply)
		*this = *this * rotationMatrixY;
	else if (combine == CombineFunc::Replace)
		*this = rotationMatrixY;
}

void EG::Matrix::RotateZ(float angle, CombineFunc combine)
{
	Matrix rotationMatrixZ = Matrix::identity;

	angle *= static_cast<float>(M_PI / 180.0f);

	rotationMatrixZ[0] = cos(angle);
	rotationMatrixZ[1] = -sin(angle);
	rotationMatrixZ[4] = sin(angle);
	rotationMatrixZ[5] = cos(angle);

	if (combine == CombineFunc::PreMultiply)
		*this = rotationMatrixZ * *this;
	else if (combine == CombineFunc::PostMultiply)
		*this = *this * rotationMatrixZ;
	else if (combine == CombineFunc::Replace)
		*this = rotationMatrixZ;
}

void EG::Matrix::Rotate(Vector3D rotation, CombineFunc combine)
{
	Matrix rotationMatrixX = Matrix::identity;
	Matrix rotationMatrixY = Matrix::identity;
	Matrix rotationMatrixZ = Matrix::identity;

	rotation *= static_cast<float>(M_PI / 180.0f);
	
	rotationMatrixX[5] = cos(rotation.x);
	rotationMatrixX[6] = -sin(rotation.x);
	rotationMatrixX[9] = sin(rotation.x);
	rotationMatrixX[10] = cos(rotation.x);

	rotationMatrixY[0] = cos(rotation.y);
	rotationMatrixY[2] = sin(rotation.y);
	rotationMatrixY[8] = -sin(rotation.y);
	rotationMatrixY[10] = cos(rotation.y);

	rotationMatrixZ[0] = cos(rotation.z);
	rotationMatrixZ[1] = -sin(rotation.z);
	rotationMatrixZ[4] = sin(rotation.z);
	rotationMatrixZ[5] = cos(rotation.z);

	Matrix matrix = rotationMatrixX * rotationMatrixY * rotationMatrixZ;

	if (combine == CombineFunc::PreMultiply)
		*this = matrix * *this;
	else if (combine == CombineFunc::PostMultiply)
		*this = *this * matrix;
	else if (combine == CombineFunc::Replace)
		*this = matrix;
}

void EG::Matrix::Translate(Vector3D translation, CombineFunc combine)
{
	Matrix translationMatrix = Matrix::identity;
	translationMatrix[3] = translation.x;
	translationMatrix[7] = translation.y;
	translationMatrix[11] = translation.z;

	if (combine == CombineFunc::PreMultiply)
		*this = translationMatrix * *this;
	else if (combine == CombineFunc::PostMultiply)
		*this = *this * translationMatrix;
	else if (combine == CombineFunc::Replace)
		*this = translationMatrix;
}

void EG::Matrix::Scale(Vector3D scale, CombineFunc combine)
{
	Matrix scaleMatrix = Matrix::identity;
	scaleMatrix[0] = scale.x;
	scaleMatrix[5] = scale.y;
	scaleMatrix[10] = scale.z;

	if (combine == CombineFunc::PreMultiply)
		*this = scaleMatrix * *this;
	else if (combine == CombineFunc::PostMultiply)
		*this = *this * scaleMatrix;
	else if (combine == CombineFunc::Replace)
		*this = scaleMatrix;
}

void EG::Matrix::ScaleRotateTranslate(Vector3D scale, Vector3D rotate, Vector3D translate, CombineFunc combine)
{
	Matrix scaleMatrix = Matrix::identity;
	Matrix rotationMatrixX = Matrix::identity;
	Matrix rotationMatrixY = Matrix::identity;
	Matrix rotationMatrixZ = Matrix::identity;
	Matrix translateMatrix = Matrix::identity;

	rotate *= static_cast<float>(M_PI / 180.0f);

	scaleMatrix[0] = scale.x;
	scaleMatrix[5] = scale.y;
	scaleMatrix[10] = scale.z;

	translateMatrix[3] = translate.x;
	translateMatrix[7] = translate.y;
	translateMatrix[11] = translate.z;

	rotationMatrixX[5] = cos(rotate.x);
	rotationMatrixX[6] = -sin(rotate.x);
	rotationMatrixX[9] = sin(rotate.x);
	rotationMatrixX[10] = cos(rotate.x);

	rotationMatrixY[0] = cos(rotate.y);
	rotationMatrixY[2] = sin(rotate.y);
	rotationMatrixY[8] = -sin(rotate.y);
	rotationMatrixY[10] = cos(rotate.y);

	rotationMatrixZ[0] = cos(rotate.z);
	rotationMatrixZ[1] = -sin(rotate.z);
	rotationMatrixZ[4] = sin(rotate.z);
	rotationMatrixZ[5] = cos(rotate.z);

	Matrix matrix = rotationMatrixX * rotationMatrixY * rotationMatrixZ;

	if (combine == CombineFunc::PreMultiply)
		*this = translateMatrix * matrix * scaleMatrix * *this;
	else if (combine == CombineFunc::PostMultiply)
		*this = *this * translateMatrix * matrix * scaleMatrix;
	else if (combine == CombineFunc::Replace)
		*this = translateMatrix * matrix * scaleMatrix;
}

void EG::Matrix::ScaleRotate(Vector3D scale, Vector3D rotate, CombineFunc combine)
{
	Matrix scaleMatrix = Matrix::identity;
	Matrix rotationMatrixX = Matrix::identity;
	Matrix rotationMatrixY = Matrix::identity;
	Matrix rotationMatrixZ = Matrix::identity;

	rotate *= static_cast<float>(M_PI / 180.0f);

	scaleMatrix[0] = scale.x;
	scaleMatrix[5] = scale.y;
	scaleMatrix[10] = scale.z;

	rotationMatrixX[5] = cos(rotate.x);
	rotationMatrixX[6] = -sin(rotate.x);
	rotationMatrixX[9] = sin(rotate.x);
	rotationMatrixX[10] = cos(rotate.x);

	rotationMatrixY[0] = cos(rotate.y);
	rotationMatrixY[2] = sin(rotate.y);
	rotationMatrixY[8] = -sin(rotate.y);
	rotationMatrixY[10] = cos(rotate.y);

	rotationMatrixZ[0] = cos(rotate.z);
	rotationMatrixZ[1] = -sin(rotate.z);
	rotationMatrixZ[4] = sin(rotate.z);
	rotationMatrixZ[5] = cos(rotate.z);

	Matrix matrix = rotationMatrixX * rotationMatrixY * rotationMatrixZ;

	if (combine == CombineFunc::PreMultiply)
		*this = matrix * scaleMatrix * *this;
	else if (combine == CombineFunc::PostMultiply)
		*this = *this * matrix * scaleMatrix;
	else if (combine == CombineFunc::Replace)
		*this = matrix * scaleMatrix;
}

void EG::Matrix::ScaleTranslate(Vector3D scale, Vector3D translate, CombineFunc combine)
{
	Matrix scaleMatrix = Matrix::identity;
	Matrix translateMatrix = Matrix::identity;

	scaleMatrix[0] = scale.x;
	scaleMatrix[5] = scale.y;
	scaleMatrix[10] = scale.z;

	translateMatrix[3] = translate.x;
	translateMatrix[7] = translate.y;
	translateMatrix[11] = translate.z;

	if (combine == CombineFunc::PreMultiply)
		*this = translateMatrix * scaleMatrix * *this;
	else if (combine == CombineFunc::PostMultiply)
		*this = *this * translateMatrix * scaleMatrix;
	else if (combine == CombineFunc::Replace)
		*this = translateMatrix * scaleMatrix;
}

void EG::Matrix::RotateTranslate(Vector3D rotate, Vector3D translate, CombineFunc combine)
{
	Matrix rotationMatrixX = Matrix::identity;
	Matrix rotationMatrixY = Matrix::identity;
	Matrix rotationMatrixZ = Matrix::identity;
	Matrix translateMatrix = Matrix::identity;

	rotate *= static_cast<float>(M_PI / 180.0f);

	translateMatrix[3] = translate.x;
	translateMatrix[7] = translate.y;
	translateMatrix[11] = translate.z;

	rotationMatrixX[5] = cos(rotate.x);
	rotationMatrixX[6] = -sin(rotate.x);
	rotationMatrixX[9] = sin(rotate.x);
	rotationMatrixX[10] = cos(rotate.x);

	rotationMatrixY[0] = cos(rotate.y);
	rotationMatrixY[2] = sin(rotate.y);
	rotationMatrixY[8] = -sin(rotate.y);
	rotationMatrixY[10] = cos(rotate.y);

	rotationMatrixZ[0] = cos(rotate.z);
	rotationMatrixZ[1] = -sin(rotate.z);
	rotationMatrixZ[4] = sin(rotate.z);
	rotationMatrixZ[5] = cos(rotate.z);

	Matrix matrix = rotationMatrixX * rotationMatrixY * rotationMatrixZ;

	if (combine == CombineFunc::PreMultiply)
		*this = translateMatrix * matrix * *this;
	else if (combine == CombineFunc::PostMultiply)
		*this = *this * translateMatrix * matrix;
	else if (combine == CombineFunc::Replace)
		*this = translateMatrix * matrix;
}

EG::Matrix& EG::Matrix::Transpose(bool createNew)
{
	Matrix tempMatrix = *this;

	tempMatrix[4] = (*this)[1];
	tempMatrix[8] = (*this)[2];
	tempMatrix[12] = (*this)[3];

	tempMatrix[1] = (*this)[4];
	tempMatrix[9] = (*this)[6];
	tempMatrix[13] = (*this)[7];

	tempMatrix[2] = (*this)[8];
	tempMatrix[6] = (*this)[9];
	tempMatrix[14] = (*this)[11];

	tempMatrix[3] = (*this)[12];
	tempMatrix[7] = (*this)[13];
	tempMatrix[11] = (*this)[14];

	if (createNew == false)
		*this = tempMatrix;

	return tempMatrix;
}

void EG::Matrix::operator*=(Matrix& rMatrix)
{
	Matrix tempMatrix = *this;
	
#pragma region Row1
	tempMatrix[0] = (*this)[0] * rMatrix[0] + (*this)[1] * rMatrix[4] + (*this)[2] * rMatrix[8] + (*this)[3] * rMatrix[12];
	tempMatrix[1] = (*this)[0] * rMatrix[1] + (*this)[1] * rMatrix[5] + (*this)[2] * rMatrix[9] + (*this)[3] * rMatrix[13];
	tempMatrix[2] = (*this)[0] * rMatrix[2] + (*this)[1] * rMatrix[6] + (*this)[2] * rMatrix[10] + (*this)[3] * rMatrix[14];
	tempMatrix[3] = (*this)[0] * rMatrix[3] + (*this)[1] * rMatrix[7] + (*this)[2] * rMatrix[11] + (*this)[3] * rMatrix[15];
#pragma  endregion

#pragma region Row2
	tempMatrix[4] = (*this)[4] * rMatrix[0] + (*this)[5] * rMatrix[4] + (*this)[6] * rMatrix[8] + (*this)[7] * rMatrix[12];
	tempMatrix[5] = (*this)[4] * rMatrix[1] + (*this)[5] * rMatrix[5] + (*this)[6] * rMatrix[9] + (*this)[7] * rMatrix[13];
	tempMatrix[6] = (*this)[4] * rMatrix[2] + (*this)[5] * rMatrix[6] + (*this)[6] * rMatrix[10] + (*this)[7] * rMatrix[14];
	tempMatrix[7] = (*this)[4] * rMatrix[3] + (*this)[5] * rMatrix[7] + (*this)[6] * rMatrix[11] + (*this)[7] * rMatrix[15];
#pragma endregion

#pragma region Row3
	tempMatrix[8] = (*this)[8] * rMatrix[0] + (*this)[9] * rMatrix[4] + (*this)[10] * rMatrix[8] + (*this)[11] * rMatrix[12];
	tempMatrix[9] = (*this)[8] * rMatrix[1] + (*this)[9] * rMatrix[5] + (*this)[10] * rMatrix[9] + (*this)[11] * rMatrix[13];
	tempMatrix[10] = (*this)[8] * rMatrix[2] + (*this)[9] * rMatrix[6] + (*this)[10] * rMatrix[10] + (*this)[11] * rMatrix[14];
	tempMatrix[11] = (*this)[8] * rMatrix[3] + (*this)[9] * rMatrix[7] + (*this)[10] * rMatrix[11] + (*this)[11] * rMatrix[15];
#pragma endregion

#pragma region Row4
	tempMatrix[12] = (*this)[12] * rMatrix[0] + (*this)[13] * rMatrix[4] + (*this)[14] * rMatrix[8] + (*this)[15] * rMatrix[12];
	tempMatrix[13] = (*this)[12] * rMatrix[1] + (*this)[13] * rMatrix[5] + (*this)[14] * rMatrix[9] + (*this)[15] * rMatrix[13];
	tempMatrix[14] = (*this)[12] * rMatrix[2] + (*this)[13] * rMatrix[6] + (*this)[14] * rMatrix[10] + (*this)[15] * rMatrix[14];
	tempMatrix[15] = (*this)[12] * rMatrix[3] + (*this)[13] * rMatrix[7] + (*this)[14] * rMatrix[11] + (*this)[15] * rMatrix[15];
#pragma endregion

	*this = tempMatrix;
}

EG::Matrix EG::Matrix::operator*(Matrix& rMatrix)
{
	Matrix tempMatrix = *this;
	
#pragma region Row1
	tempMatrix[0] = (*this)[0] * rMatrix[0] + (*this)[1] * rMatrix[4] + (*this)[2] * rMatrix[8] + (*this)[3] * rMatrix[12];
	tempMatrix[1] = (*this)[0] * rMatrix[1] + (*this)[1] * rMatrix[5] + (*this)[2] * rMatrix[9] + (*this)[3] * rMatrix[13];
	tempMatrix[2] = (*this)[0] * rMatrix[2] + (*this)[1] * rMatrix[6] + (*this)[2] * rMatrix[10] + (*this)[3] * rMatrix[14];
	tempMatrix[3] = (*this)[0] * rMatrix[3] + (*this)[1] * rMatrix[7] + (*this)[2] * rMatrix[11] + (*this)[3] * rMatrix[15];
#pragma  endregion

#pragma region Row2
	tempMatrix[4] = (*this)[4] * rMatrix[0] + (*this)[5] * rMatrix[4] + (*this)[6] * rMatrix[8] + (*this)[7] * rMatrix[12];
	tempMatrix[5] = (*this)[4] * rMatrix[1] + (*this)[5] * rMatrix[5] + (*this)[6] * rMatrix[9] + (*this)[7] * rMatrix[13];
	tempMatrix[6] = (*this)[4] * rMatrix[2] + (*this)[5] * rMatrix[6] + (*this)[6] * rMatrix[10] + (*this)[7] * rMatrix[14];
	tempMatrix[7] = (*this)[4] * rMatrix[3] + (*this)[5] * rMatrix[7] + (*this)[6] * rMatrix[11] + (*this)[7] * rMatrix[15];
#pragma endregion

#pragma region Row3
	tempMatrix[8] = (*this)[8] * rMatrix[0] + (*this)[9] * rMatrix[4] + (*this)[10] * rMatrix[8] + (*this)[11] * rMatrix[12];
	tempMatrix[9] = (*this)[8] * rMatrix[1] + (*this)[9] * rMatrix[5] + (*this)[10] * rMatrix[9] + (*this)[11] * rMatrix[13];
	tempMatrix[10] = (*this)[8] * rMatrix[2] + (*this)[9] * rMatrix[6] + (*this)[10] * rMatrix[10] + (*this)[11] * rMatrix[14];
	tempMatrix[11] = (*this)[8] * rMatrix[3] + (*this)[9] * rMatrix[7] + (*this)[10] * rMatrix[11] + (*this)[11] * rMatrix[15];
#pragma endregion

#pragma region Row4
	tempMatrix[12] = (*this)[12] * rMatrix[0] + (*this)[13] * rMatrix[4] + (*this)[14] * rMatrix[8] + (*this)[15] * rMatrix[12];
	tempMatrix[13] = (*this)[12] * rMatrix[1] + (*this)[13] * rMatrix[5] + (*this)[14] * rMatrix[9] + (*this)[15] * rMatrix[13];
	tempMatrix[14] = (*this)[12] * rMatrix[2] + (*this)[13] * rMatrix[6] + (*this)[14] * rMatrix[10] + (*this)[15] * rMatrix[14];
	tempMatrix[15] = (*this)[12] * rMatrix[3] + (*this)[13] * rMatrix[7] + (*this)[14] * rMatrix[11] + (*this)[15] * rMatrix[15];
#pragma endregion

	return tempMatrix;
}

void EG::Matrix::operator+=(Matrix& rMatrix)
{
	for (int i = 0; i < 16; i++)
		(*this)[i] += rMatrix[i];
}

EG::Matrix EG::Matrix::operator+(Matrix& rMatrix)
{
	Matrix newMatrix;

	for (int i = 0; i < 16; i++)
		newMatrix[i] = (*this)[i] + rMatrix[i];

	return newMatrix;
}

void EG::Matrix::operator-=(Matrix& rMatrix)
{
	for (int i = 0; i < 16; i++)
		(*this)[i] -= rMatrix[i];
}

EG::Matrix EG::Matrix::operator-(Matrix& rMatrix)
{
	Matrix newMatrix;

	for (int i = 0; i < 16; i++)
		newMatrix[i] = (*this)[i] + rMatrix[i];

	return newMatrix;
}

void EG::Matrix::ApplyPerspectiveMatrix(float aspect, float fov, float nearPlane, float farPlane)
{
	// double cotan(double i) { return(1 / tan(i)); }

	(*this)[0] = 1.0f / tan(fov / 2) / aspect;
	(*this)[5] = 1.0f / tan(fov / 2);
	(*this)[10] = farPlane / (farPlane - nearPlane);
	(*this)[11] = 1.0f;
	(*this)[14] = -(farPlane * nearPlane / (farPlane - nearPlane));
 }

void EG::Matrix::ApplyOrthoMatrix(float width, float height, float nearPlane, float farPlane)
{
	*this = Matrix::identity;
	(*this)[0] = 2 / width;
	(*this)[5] = 2 / height;
	(*this)[10] = 1 / (farPlane - nearPlane);
	(*this)[14] = nearPlane / (nearPlane - farPlane);
}

void EG::Matrix::ApplyViewMatrix(Vector3D cameraPos, Vector3D cameraLookAt)
{
	Matrix tempMatrix = Matrix::identity;
	Vector3D up = Vector3D(0.0f, 1.0f, 0.0f);

	Vector3D zAxis = cameraLookAt - cameraPos;
	zAxis.Normilize();

	Vector3D xAxis = up.CrossProduct(zAxis);
	xAxis.Normilize();

	Vector3D yAxis = zAxis.CrossProduct(xAxis);

	tempMatrix[0] = xAxis.x;
	tempMatrix[1] = yAxis.x;
	tempMatrix[2] = zAxis.x;
	tempMatrix[4] = xAxis.y;
	tempMatrix[5] = yAxis.y;
	tempMatrix[6] = zAxis.y;
	tempMatrix[8] = xAxis.z;
	tempMatrix[9] = yAxis.z;
	tempMatrix[10] = zAxis.z;
	tempMatrix[12] = -xAxis.DotProduct(cameraPos);
	tempMatrix[13] = -yAxis.DotProduct(cameraPos);
	tempMatrix[14] = -zAxis.DotProduct(cameraPos);

	*this = tempMatrix;
}
