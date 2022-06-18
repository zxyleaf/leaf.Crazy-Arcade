#ifndef SUMMONDUMMY_H_
#define SUMMONDUMMY_H_


#include <map.h>
#include <bomb.h>
#include <QVector>
#include <component.h>
#include <gamescene.h>
#include <imagetransform.h>
class SummonDummy : public Component {
 public:
  SummonDummy();

  void onAttach() override;
  bool getend();
  void onClick(QGraphicsSceneMouseEvent *ev) override;
  bool end = 0;
  bool m = 0;
protected:
  Transform *transform = nullptr;

};

#endif  // SUMMONDUMMY_H_
