using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Media3D;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Geology3D
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		public
			PerspectiveCamera Camera = new PerspectiveCamera();

			Point MouseLastPosition;
			Point MouseCurrentPosition;

			Point3D Origin = new Point3D(0, 0, 0);
			Vector3D XAxis = new Vector3D(1, 0, 0);

			Vector3D CameraVector;
			double CameraAngleX = 0.0;
			double CameraAngleZ = 0.0;
			double CameraDistanceToOrigin;
			AxisAngleRotation3D CameraRotationX = new AxisAngleRotation3D();
			AxisAngleRotation3D CameraRotationZ = new AxisAngleRotation3D();

		public MainWindow()
		{
			InitializeComponent();

			Canvas3D.MouseMove += Canvas3DMouseMove;
			Canvas3D.MouseUp += Canvas3DMouseUp;
			Canvas3D.MouseDown += Canvas3DMouseDown;
			
			Model3DGroup ModelsGroup = new Model3DGroup();
			ModelVisual3D GModelVisual3D = new ModelVisual3D();

			GeometryModel3D CubeGeometryModel = new GeometryModel3D();
			GeometryModel3D PlaneGeometryModel = new GeometryModel3D();

			//PerspectiveCamera Camera = new PerspectiveCamera();

			// Specify where in the 3D scene the camera is.
			Camera.Position = new Point3D(-5, 5, -5);

			// Specify the direction that the camera is pointing.
			Camera.LookDirection = new Vector3D(1, -1, 1);

			// Asign the camera to the viewport
			ViewPort3D.Camera = Camera;

			// Define the lights cast in the scene. Without light, the 3D object cannot 
			// be seen. Note: to illuminate an object from additional directions, create 
			// additional lights.
			DirectionalLight GDirectionalLight = new DirectionalLight();
			GDirectionalLight.Color = Colors.White;
			GDirectionalLight.Direction = new Vector3D(-1, -1, -1);

			//AmbientLight AmbLight = new AmbientLight(System.Windows.Media.Brushes.White.Color);

			ModelsGroup.Children.Add(GDirectionalLight);
			//ModelsGroup.Children.Add(AmbLight);

			// The material specifies the material applied to the 3D object.
			// Define material and apply to the mesh geometries.
			DiffuseMaterial BlueMaterial = new DiffuseMaterial(new SolidColorBrush(Colors.DodgerBlue));
			DiffuseMaterial PlaneMaterial = new DiffuseMaterial(new SolidColorBrush(Colors.Gray));

			CubeGeometryModel.Material = BlueMaterial;
			PlaneGeometryModel.Material = PlaneMaterial;

			// Apply the mesh to the geometry model.
			CubeGeometryModel.Geometry = DrawCube();
			PlaneGeometryModel.Geometry = DrawPlane();

			// Apply a transform to the object. In this sample, a rotation transform is applied,  
			// rendering the 3D object rotated.
			RotateTransform3D GRotateTransform3D = new RotateTransform3D();
			AxisAngleRotation3D GAxisAngleRotation3d = new AxisAngleRotation3D();
			GAxisAngleRotation3d.Axis = new Vector3D(0, 1, 0);
			GAxisAngleRotation3d.Angle = 0;
			GRotateTransform3D.Rotation = GAxisAngleRotation3d;
			CubeGeometryModel.Transform = GRotateTransform3D;

			// Add the geometry model to the model group.
			ModelsGroup.Children.Add(CubeGeometryModel);
			ModelsGroup.Children.Add(PlaneGeometryModel);

			// Add the group of models to the ModelVisual3d.
			GModelVisual3D.Content = ModelsGroup;

			ViewPort3D.Children.Add(GModelVisual3D);

			CameraVector = (Camera.Position - Origin);

			CameraDistanceToOrigin = CameraVector.Length;
			//LabelTest.Content = CameraVector.Length;

			CameraVector.Normalize();
			XAxis.Normalize();

			//CameraAngle = (Math.Acos(Vector3D.DotProduct(CameraVector, XAxis))) * (180 / Math.PI);

			//LabelTest.Content = (Math.Acos(Vector3D.DotProduct(CameraVector, XAxis)))*(180/Math.PI);
			//LabelTest.Content = Vector3D.DotProduct(CameraVector, XAxis);
			//LabelTest.Content = CameraVector;
			LabelTest.Content = new RotateTransform3D(new AxisAngleRotation3D(new Vector3D(0, 1, 0), 10));

			//LabelTest.Content = Geology3D_MainWindow.PointToScreen(Mouse.GetPosition(Geology3D_MainWindow));
		}

		private void Canvas3DMouseDown(object sender, MouseButtonEventArgs e)
		{
			Canvas3D.CaptureMouse();

			MouseLastPosition = Mouse.GetPosition(Canvas3D);
		}

		private void Canvas3DMouseMove(object sender, MouseEventArgs e)
		{
			if (Canvas3D.IsMouseCaptured)
			{
				RotateCamera();
			}
		}

		private void Canvas3DMouseUp(object sender, MouseButtonEventArgs e)
		{
			Canvas3D.ReleaseMouseCapture();
		}

		MeshGeometry3D DrawCube()
		{
			// The geometry specifes the shape of the 3D Cube
			MeshGeometry3D Cube = new MeshGeometry3D();

			double x = 0.5;
			double z = 1.0;

			// Create a collection of vertex positions for the MeshGeometry3D. 
			Point3DCollection CubeCorners = new Point3DCollection();
			// UP NE
			CubeCorners.Add(new Point3D(x, z, x));
			// UP NW
			CubeCorners.Add(new Point3D(-x, z, x));
			// DOWN NE
			CubeCorners.Add(new Point3D(-x, 0, x));
			// DOWN NE
			CubeCorners.Add(new Point3D(x, 0, x));
			// UP SE
			CubeCorners.Add(new Point3D(x, z, -x));
			// UP SW
			CubeCorners.Add(new Point3D(-x, z, -x));
			// DOWN SW
			CubeCorners.Add(new Point3D(-x, 0, -x));
			// DOWN SE
			CubeCorners.Add(new Point3D(x, 0, -x));
			Cube.Positions = CubeCorners;

			Int32[] indices ={
					//front
						  0,1,2,
						  0,2,3,
					//back
						  4,7,6,
						  4,6,5,
					//Right
						  4,0,3,
						  4,3,7,
					//Left
						  1,5,6,
						  1,6,2,
					//Top
						  1,0,4,
						  1,4,5,
					//Bottom
						  2,6,7,
						  2,7,3};

			// Create a collection of triangle indices for the MeshGeometry3D.
			Int32Collection CubeTriangles = new Int32Collection();

			foreach (Int32 index in indices)
			{
				CubeTriangles.Add(index);
			}

			Cube.TriangleIndices = CubeTriangles;

			return Cube;
		}

		MeshGeometry3D DrawPlane()
		{
			// The geometry specifes the shape of the 3D plane
			MeshGeometry3D Plane = new MeshGeometry3D();

			int x = 2;

			// Create a collection of vertex positions for the MeshGeometry3D. 
			Point3DCollection PlaneCorners = new Point3DCollection();
			PlaneCorners.Add(new Point3D(x, 0, x));
			PlaneCorners.Add(new Point3D(-x, 0, -x));
			PlaneCorners.Add(new Point3D(x, 0, -x));
			PlaneCorners.Add(new Point3D(-x, 0, x));
			Plane.Positions = PlaneCorners;

			Int32[] indices ={0,2,1,0,1,3
							};

			// Create a collection of triangle indices for the MeshGeometry3D.
			Int32Collection PlaneTriangles = new Int32Collection();

			foreach (Int32 index in indices)
			{
				PlaneTriangles.Add(index);
			}

			Plane.TriangleIndices = PlaneTriangles;

			return Plane;
		}

		void RotateCamera()
		{
			MouseCurrentPosition = Mouse.GetPosition(Canvas3D);

			double dx = MouseCurrentPosition.X - MouseLastPosition.X;
			double dy = MouseCurrentPosition.Y - MouseLastPosition.Y;

			// TODO CameraAngle always increase, sometimes the number are too big
			// TODO reset the angle when angle == 360 (or - 360), make angle == 0
			CameraAngleX += dx;
			CameraAngleZ += dy;

			CameraRotationX.Axis = new Vector3D(0, 1, 0);
			CameraRotationX.Angle = -CameraAngleX;
			CameraRotationZ.Axis = new Vector3D(0, 0, 1); 
			CameraRotationZ.Angle = -CameraAngleZ;

			// TODO make a vector perpendicular to the vector from the origin to the camera.
			// The camera Z rotation should be around this vector X component

			Transform3DGroup T3DGroup = new Transform3DGroup();

			T3DGroup.Children.Add(new RotateTransform3D(CameraRotationX));
			T3DGroup.Children.Add(new RotateTransform3D(CameraRotationZ));

			ViewPort3D.Camera.Transform = T3DGroup;

			MouseLastPosition = Mouse.GetPosition(Canvas3D);

			LabelTest.Content = CameraAngleX;
		}
	}
}
