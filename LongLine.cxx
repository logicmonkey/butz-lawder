#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkLine.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include "hilbert_generated_points.h"

int main(int, char*[])
{
  // Create five points.
  double origin[3] = {0.0, 0.0, 0.0};

  // Create a vtkPoints object and store the points in it
  vtkNew<vtkPoints> points;
  points->InsertNextPoint(origin);

  for (unsigned int i = 0; i < VERTS; i++)
    points->InsertNextPoint(p[i]);

  // Create a cell array to store the lines in and add the lines to it
  vtkNew<vtkCellArray> lines;

  for (unsigned int i = 0; i < VERTS; i++)
  {
    vtkNew<vtkLine> line;
    line->GetPointIds()->SetId(0, i);
    line->GetPointIds()->SetId(1, i + 1);
    lines->InsertNextCell(line);
  }

  // Create a polydata to store everything in
  vtkNew<vtkPolyData> linesPolyData;

  // Add the points to the dataset
  linesPolyData->SetPoints(points);

  // Add the lines to the dataset
  linesPolyData->SetLines(lines);

  // Setup actor and mapper
  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputData(linesPolyData);

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);
  actor->GetProperty()->SetLineWidth(4);
  actor->GetProperty()->SetColor(colors->GetColor3d("Orange").GetData());

  // Setup render window, renderer, and interactor
  vtkNew<vtkRenderer> renderer;
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->SetWindowName("LongLine");
  renderWindow->AddRenderer(renderer);
  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Azimuth(30);
  renderer->GetActiveCamera()->Elevation(30);
  renderer->ResetCameraClippingRange();

  renderer->SetBackground(colors->GetColor3d("Black").GetData());
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
