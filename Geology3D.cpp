#include "vtkAutoInit.h" 
VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType)

#include "string"
#include "sstream"
#include "vtkSmartPointer.h"
#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTerrain.h"
#include "vtkRenderer.h"
#include "vtkNamedColors.h"
#include "vtkCubeSource.h"
#include "vtkSphereSource.h"
#include "vtkProperty.h"
#include "vtkAnnotatedCubeActor.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkAxesActor.h"
#include "vtkCubeAxesActor.h"
#include "vtkAxisActor.h"
#include "vtkTextActor.h"
#include "vtkTextProperty.h"
#include "vtkCallbackCommand.h"
#include "vtkMath.h"
#include "vtkTimerLog.h"
#include "vtkOrientedGlyphContourRepresentation.h"
#include "vtkContourWidget.h"
#include "vtkLine.h"
#include "vtkBillboardTextActor3D.h"

vtkNamedColors *colors = vtkNamedColors::New();
vtkTextActor *textActor = vtkTextActor::New();

void CreateCube(vtkRenderer *renderer);
void CreateOrientationCube(vtkRenderWindowInteractor *Interactor);
void CreateOrientationAxes(vtkRenderWindowInteractor *Interactor);
void CreateCubeAxesActor(vtkRenderer *renderer);
void CreateLines(vtkRenderer *renderer, float d);

void KeypressCallbackFunction(vtkObject* caller, long unsigned int eventId,	void* clientData, void* callData);
static void CallbackFunction(vtkObject* caller, long unsigned int eventId, 	void* clientData, void* callData);

void ActorCallback(vtkObject* caller, long unsigned int vtkNotUsed(eventId), void* clientData, void* vtkNotUsed(callData))
{
	vtkSmartPointer<vtkBillboardTextActor3D> textActor = static_cast<vtkBillboardTextActor3D *>(clientData);
	vtkSmartPointer<vtkActor> actor = static_cast<vtkActor *>(caller);
	std::ostringstream label;
	label << std::setprecision(3)
		<< actor->GetPosition()[0] << ", "
		<< actor->GetPosition()[1] << ", "
		<< actor->GetPosition()[2] << std::endl;
	textActor->SetPosition(actor->GetPosition());
	textActor->SetInput(label.str().c_str());
}

class CustomCubeAxesActor : public vtkCubeAxesActor
{
public:
	static CustomCubeAxesActor* New();
	vtkTypeMacro(CustomCubeAxesActor, vtkCubeAxesActor);

	vtkAxisActor* GetXAxes()
	{
		return *XAxes;
	}
};

vtkStandardNewMacro(CustomCubeAxesActor);

//class CustomInteractorStyle(vtk.vtkInteractorStyleTerrain) :
//
//	def __init__(self, parent = None) :
//	self.AddObserver("LeftButtonPressEvent", self.LeftButtonPressEvent)
//	self.AddObserver("LeftButtonReleaseEvent", self.LeftButtonReleaseEvent)
//	self.AddObserver("MouseMoveEvent", self.MouseMoveEvent)
//
//	self.picker = vtk.vtkPropPicker()
//	self.worldPicker = vtk.vtkWorldPointPicker()
//
//	def MouseMoveEvent(self, obj, event) :
//	self.renderer = self.GetInteractor().GetRenderWindow().GetRenderers().GetFirstRenderer()
//	self.renderer.AddActor(txt)
//
//	clickPos = self.GetInteractor().GetEventPosition()
//
//	self.worldPicker.Pick(clickPos[0], clickPos[1], 0, self.renderer)
//	worldPos = self.worldPicker.GetPickPosition()
//
//	// txt.SetInput(str(self.GetInteractor().GetEventPosition()))
//	txt.SetInput(str(worldPos))
//
//	self.OnMouseMove()
//	return
//
//	def LeftButtonPressEvent(self, obj, event) :
//	#print(self.GetInteractor().GetEventPosition())
//
//	self.renderer = self.GetInteractor().GetRenderWindow().GetRenderers().GetFirstRenderer()
//
//	clickPos = self.GetInteractor().GetEventPosition()
//	self.picker.Pick(clickPos[0], clickPos[1], 0, self.renderer)
//	pos = self.picker.GetPickPosition()
//
//	self.worldPicker.Pick(clickPos[0], clickPos[1], 0, self.renderer)
//	worldPos = self.worldPicker.GetPickPosition()
//
//	// print(pos)
//
//	self.renderer.AddActor(txt)
//	// txt.SetInput(str(self.GetInteractor().GetEventPosition()))
//	txt.SetInput(str(worldPos))
//
//	self.OnLeftButtonDown()
//	return
//
//	def LeftButtonReleaseEvent(self, obj, event) :
//	// print("Left Button released")
//	self.OnLeftButtonUp()
//	return

int main(int, char *[])
{
	// Create a renderer, render window, and interactor
	vtkRenderer *renderer = vtkRenderer::New();
	vtkRenderWindow *renderWindow = vtkRenderWindow::New();
	renderWindow->SetWindowName("Teste");
	renderWindow->AddRenderer(renderer);
	// renderWindow.SetSize(800, 600)
	// renderWindow.SetFullScreen(True)
	renderWindow->SetSize(renderWindow->GetScreenSize());
	vtkRenderWindowInteractor *Interactor = vtkRenderWindowInteractor::New();
	Interactor->SetRenderWindow(renderWindow);

	// style = vtk.vtkInteractorStyleTrackballCamera()
	vtkInteractorStyleTerrain *style = vtkInteractorStyleTerrain::New();
	// style = CustomInteractorStyle()
	Interactor->SetInteractorStyle(style);

	textActor->GetTextProperty()->SetFontFamilyToArial();
	textActor->GetTextProperty()->BoldOn();
	textActor->GetTextProperty()->SetFontSize(20);
	textActor->GetTextProperty()->SetColor(colors->GetColor3d("white").GetData());
	textActor->SetDisplayPosition(20, 700);
	//textActor->SetInput("hello");

	renderer->AddActor(textActor);

	// distance from origin to camera. This parameter serves all other elements 
	// on 3D space to scale accordingly
	float d = 100.0;

	//CreateCube(renderer);
	CreateOrientationCube(Interactor);
	CreateOrientationAxes(Interactor);
	CreateLines(renderer, d);
	//CreateCubeAxesActor(renderer);
	
	renderer->GetActiveCamera()->SetPosition(-d, d, d);
	renderer->GetActiveCamera()->ParallelProjectionOn();
	renderer->GetActiveCamera()->SetParallelScale(d);
	renderer->GetActiveCamera()->SetClippingRange(1.0, 1000.0);

	renderer->SetBackground(colors->GetColor3d("Black").GetData());

	// function to print FPS on screen
	vtkCallbackCommand *callback = vtkCallbackCommand::New();
	callback->SetCallback(CallbackFunction);
	renderer->AddObserver(vtkCommand::EndEvent, callback);

	vtkCallbackCommand *keypressCallback = vtkCallbackCommand::New();
	keypressCallback->SetCallback(KeypressCallbackFunction);
	Interactor->AddObserver(vtkCommand::KeyPressEvent, keypressCallback);

	//  Render and interact
	renderWindow->Render();
	Interactor->Start();

	return 0;
}

void CallbackFunction(vtkObject* caller, long unsigned int vtkNotUsed(eventId), void* vtkNotUsed(clientData), void* vtkNotUsed(callData))
{
	vtkRenderer* renderer = static_cast<vtkRenderer*>(caller);

	double timeInSeconds = renderer->GetLastRenderTimeInSeconds();
	double fps = 1.0 / timeInSeconds;
	
	/*std::cout << "FPS: " << fps << std::endl;
	std::cout << "Callback" << std::endl;*/

	std::string fpsString = std::to_string(fps);
	const char *fpsChar = fpsString.c_str();
	textActor->SetInput(fpsChar);
}

void KeypressCallbackFunction(vtkObject* caller, long unsigned int vtkNotUsed(eventId), void* vtkNotUsed(clientData), void* vtkNotUsed(callData))
{
	vtkRenderWindowInteractor *Interactor = static_cast<vtkRenderWindowInteractor*>(caller);

	std::string key = Interactor->GetKeySym();

	if (key == "n")
	{
		vtkOrientedGlyphContourRepresentation *contourRep = vtkOrientedGlyphContourRepresentation::New();
		contourRep->GetLinesProperty()->SetColor(colors->GetColor3d("red").GetData());

		vtkContourWidget *contourWidget = vtkContourWidget::New();
		contourWidget->SetInteractor(Interactor);
		contourWidget->SetRepresentation(contourRep);
		contourWidget->On();
	}
}

void CreateCubeAxesActor(vtkRenderer *renderer)
{
	float Bound = 50.0;

	//vtkCubeAxesActor *cubeAxesActor = vtkCubeAxesActor::New();

	CustomCubeAxesActor *cubeAxesActor = CustomCubeAxesActor::New();
	cubeAxesActor->SetCamera(renderer->GetActiveCamera());
	cubeAxesActor->SetBounds(-Bound, Bound, -Bound, Bound, -Bound, Bound);
	cubeAxesActor->GetTitleTextProperty(0)->SetColor(1.0, 0.0, 0.0);
	cubeAxesActor->GetLabelTextProperty(0)->SetColor(1.0, 0.0, 0.0);

	cubeAxesActor->GetTitleTextProperty(1)->SetColor(0.0, 1.0, 0.0);
	cubeAxesActor->GetLabelTextProperty(1)->SetColor(0.0, 1.0, 0.0);

	cubeAxesActor->GetTitleTextProperty(2)->SetColor(0.0, 0.0, 1.0);
	cubeAxesActor->GetLabelTextProperty(2)->SetColor(0.0, 0.0, 1.0);

	cubeAxesActor->SetScreenSize(40.0);

	cubeAxesActor->GetXAxes()->SetDeltaMajor(1, 5.0);
	cubeAxesActor->GetXAxes()->SetDeltaMinor(5.0);
	//std::cout << cubeAxesActor->GetXAxes()->GetDeltaMajor(2) << "\n";
	//std::cout << cubeAxesActor->GetXAxes()->GetDeltaMinor() << "\n";

	cubeAxesActor->DrawXGridlinesOn();
	cubeAxesActor->DrawYGridlinesOn();
	cubeAxesActor->DrawZGridlinesOn();

	#if VTK_MAJOR_VERSION == 6
		cubeAxesActor->SetGridLineLocation(VTK_GRID_LINES_FURTHEST);
	#endif
	#if VTK_MAJOR_VERSION > 6
		cubeAxesActor->SetGridLineLocation(
			cubeAxesActor->VTK_GRID_LINES_FURTHEST);
	#endif

	cubeAxesActor->XAxisMinorTickVisibilityOff();
	cubeAxesActor->YAxisMinorTickVisibilityOff();
	cubeAxesActor->ZAxisMinorTickVisibilityOff();

	//cubeAxesActor->SetDrawXInnerGridlines(1);
	//cubeAxesActor->SetDrawXGridpolys(1);
	//cubeAxesActor->SetTickLocation(1);
	//cubeAxesActor->SetGridLineLocation(2);
	//cubeAxesActor->SetXAxisRange(-50.0, 50.0);
	//cubeAxesActor->SetLabelScaling(true, 100, 10, 10);

	renderer->AddActor(cubeAxesActor);

	renderer->ResetCamera();
}

void CreateCube(vtkRenderer *renderer)
{
	vtkCubeSource *cube = vtkCubeSource::New();

	float Bounds = 25.0;

	cube->SetBounds(-Bounds, Bounds, -Bounds, Bounds, -Bounds, Bounds);
	cube->Update();

	// mapper
	vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
	cubeMapper->SetInputData(cube->GetOutput());

	// Actor.
	vtkActor *cubeActor = vtkActor::New();
	cubeActor->SetMapper(cubeMapper);

	cubeActor->GetProperty()->SetColor(colors->GetColor3d("SkyBlue").GetData());

	// Assign actor to the renderer.
	renderer->AddActor(cubeActor);
}

void CreateOrientationCube(vtkRenderWindowInteractor *Interactor)
{
	vtkAnnotatedCubeActor *axesActor = vtkAnnotatedCubeActor::New();
		
	axesActor->SetYPlusFaceText("TOP");
	axesActor->SetYMinusFaceText("BOTTOM");

	axesActor->SetZPlusFaceText("FRONT");
	axesActor->SetZMinusFaceText("BACK");

	axesActor->SetXPlusFaceText("RIGHT");
	axesActor->SetXMinusFaceText("LEFT");

	axesActor->SetYFaceTextRotation(90.0);
	axesActor->SetZFaceTextRotation(90.0);
	axesActor->SetXFaceTextRotation(-90.0);

	axesActor->SetFaceTextScale(0.14);

	axesActor->GetTextEdgesProperty()->SetColor(colors->GetColor3d("white").GetData());
	axesActor->GetTextEdgesProperty()->SetLineWidth(2);
	axesActor->GetCubeProperty()->SetColor(colors->GetColor3d("silver").GetData());
	vtkOrientationMarkerWidget *CubeWidget = vtkOrientationMarkerWidget::New();
	CubeWidget->SetOrientationMarker(axesActor);
	CubeWidget->SetViewport(0.9, 0.8, 1.0, 1.0);

	CubeWidget->SetInteractor(Interactor);
	CubeWidget->EnabledOn();

	CubeWidget->InteractiveOn();
}

void CreateOrientationAxes(vtkRenderWindowInteractor *Interactor)
{
	vtkAxesActor *axes = vtkAxesActor::New();

	axes->SetXAxisLabelText("Y");
	axes->SetYAxisLabelText("Z");
	axes->SetZAxisLabelText("X");

	axes->GetXAxisShaftProperty()->SetColor((colors->GetColor3d("green").GetData()));
	axes->GetXAxisTipProperty()->SetColor((colors->GetColor3d("green").GetData()));

	axes->GetYAxisShaftProperty()->SetColor((colors->GetColor3d("blue").GetData()));
	axes->GetYAxisTipProperty()->SetColor((colors->GetColor3d("blue").GetData()));

	axes->GetZAxisShaftProperty()->SetColor((colors->GetColor3d("red").GetData()));
	axes->GetZAxisTipProperty()->SetColor((colors->GetColor3d("red").GetData()));

	vtkOrientationMarkerWidget *widget = vtkOrientationMarkerWidget::New();
	double rgba[4]{ 0.0, 0.0, 0.0, 0.0 };
	colors->GetColor("Carrot", rgba);
	widget->SetOutlineColor(rgba[0], rgba[1], rgba[2]);
	widget->SetOrientationMarker(axes);
	widget->SetInteractor(Interactor);
	widget->SetViewport(0.0, 0.0, 0.1, 0.2);
	widget->SetEnabled(1);
	widget->InteractiveOn();
}

void CreateLines(vtkRenderer *renderer, float d)
{
	// Create the polydata where we will store all the geometric data
	vtkPolyData *linesPolyData = vtkPolyData::New();
	
	double points[8][3] = {
		{ -d / 2, -d / 2, -d / 2 },
		{ d / 2, -d / 2, -d / 2 },
		{ d / 2, -d / 2, d / 2 },
		{ -d / 2, -d / 2, d / 2 },
		{ -d / 2, d / 2, -d / 2 },
		{ d / 2, d / 2, -d / 2 },
		{ d / 2, d / 2, d / 2 },
		{ -d / 2, d / 2, d / 2 },
	};

	// Create a vtkPoints container and store the points in it
	vtkPoints *pts = vtkPoints::New();

	//std::cout << points[0] << std::endl;

	for (int i = 0; i < 8; i++)
	{
		pts->InsertNextPoint(points[i]);

		//plot position of each point on the screen, with billboards

		/*std::string PointPos = std::to_string(points[i][0]) + 
			std::to_string(points[i][1]) + 
			std::to_string(points[i][2]);

		const char *PointPosChar = PointPos.c_str();

		vtkBillboardTextActor3D *textActor = vtkBillboardTextActor3D::New();
		textActor->SetInput(PointPosChar);
		textActor->SetPosition(points[i]);
		textActor->GetTextProperty()->SetFontSize(12);
		textActor->GetTextProperty()->SetColor(1.0, 1.0, .4);
		textActor->GetTextProperty()->SetJustificationToCentered();

		renderer->AddActor(textActor);

		vtkCallbackCommand *actorCallback = vtkCallbackCommand::New();
		actorCallback->SetCallback(ActorCallback);
		actorCallback->SetClientData(textActor);
		textActor->AddObserver(vtkCommand::ModifiedEvent, actorCallback);*/
	}

	// Add the points to the polydata container
	linesPolyData->SetPoints(pts);

	// Create an array of lines
	vtkLine *line[12];
	// Create a vtkCellArray container and store the lines in it
	vtkCellArray *lines = vtkCellArray::New();

	for (int i = 0; i < 12; i++)
	{
		line[i] = vtkLine::New();

		if (i == 0)
		{
			line[i]->GetPointIds()->SetId(0, 0);
			line[i]->GetPointIds()->SetId(1, 1);
		}
		else if (i == 1)
		{
			line[i]->GetPointIds()->SetId(0, 1);
			line[i]->GetPointIds()->SetId(1, 2);
		}
		else if (i == 2)
		{
			line[i]->GetPointIds()->SetId(0, 2);
			line[i]->GetPointIds()->SetId(1, 3);
		}
		else if (i == 3)
		{
			line[i]->GetPointIds()->SetId(0, 3);
			line[i]->GetPointIds()->SetId(1, 0);
		}
		else if (i == 4)
		{
			line[i]->GetPointIds()->SetId(0, 4);
			line[i]->GetPointIds()->SetId(1, 5);
		}
		else if (i == 5)
		{
			line[i]->GetPointIds()->SetId(0, 5);
			line[i]->GetPointIds()->SetId(1, 6);
		}
		else if (i == 6)
		{
			line[i]->GetPointIds()->SetId(0, 6);
			line[i]->GetPointIds()->SetId(1, 7);
		}
		else if (i == 7)
		{
			line[i]->GetPointIds()->SetId(0, 7);
			line[i]->GetPointIds()->SetId(1, 4);
		}
		else if (i == 8)
		{
			line[i]->GetPointIds()->SetId(0, 0);
			line[i]->GetPointIds()->SetId(1, 4);
		}
		else if (i == 9)
		{
			line[i]->GetPointIds()->SetId(0, 1);
			line[i]->GetPointIds()->SetId(1, 5);
		}
		else if (i == 10)
		{
			line[i]->GetPointIds()->SetId(0, 2);
			line[i]->GetPointIds()->SetId(1, 6);
		}
		else if (i == 11)
		{
			line[i]->GetPointIds()->SetId(0, 3);
			line[i]->GetPointIds()->SetId(1, 7);
		}

		lines->InsertNextCell(line[i]);
	}   

	// Add the lines to the polydata container
	linesPolyData->SetLines(lines);

	// Setup the visualization pipeline
	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	mapper->SetInputData(linesPolyData);

	vtkActor *actor = vtkActor::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetLineWidth(1);

	renderer->AddActor(actor);
}
