#ifndef ANNOTATIONINTERACTIONMODE_H
#define ANNOTATIONINTERACTIONMODE_H

#include <SliceWindowInteractionDelegateWidget.h>
#include <SNAPCommon.h>

class GenericSliceModel;
class GenericSliceView;
class AnnotationModel;
class AnnotationRenderer;

class AnnotationInteractionMode : public SliceWindowInteractionDelegateWidget
{
  Q_OBJECT

public:
  explicit AnnotationInteractionMode(GenericSliceView *parent = 0);
  ~AnnotationInteractionMode();

  irisGetMacro(Model, AnnotationModel *)
  void SetModel(AnnotationModel *model);

  irisGetMacro(Renderer, AnnotationRenderer *)

  void mousePressEvent(QMouseEvent *ev);
  void mouseMoveEvent(QMouseEvent *ev);
  void mouseReleaseEvent(QMouseEvent *ev);

public slots:

  void onAcceptAction();

  void onModelUpdate(const EventBucket &bucket);

protected:

  AnnotationModel *m_Model;
  SmartPtr<AnnotationRenderer> m_Renderer;
};

#endif // ANNOTATIONINTERACTIONMODE_H
