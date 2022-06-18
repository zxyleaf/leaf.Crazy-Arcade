#ifndef TRANSFORMBUILDER_H
#define TRANSFORMBUILDER_H

#include <gameobject.h>
#include <imagetransform.h>
#include <transform.h>

#include <type_traits>

#define BUILDER_DEFINE_FIELD(_type, field) \
 public:                                   \
  Self &field(_type _##field) {            \
    this->_##field = _##field;             \
    return *(Self *)this;                  \
  }                                        \
                                           \
 protected:                                \
  std::remove_cv<std::remove_reference<_type>::type>::type _##field;

#define BUILDER_BUILD(field) transform->field(_##field)

template <class T1, class T2> // 类模板
class _TransformBuilder {
 public:
  using Self = T1;
  using Target = T2;

  explicit _TransformBuilder() {} // explicit关键字的作用就是防止类构造函数的隐式自动转换.对有一个参数的类构造函数有效,当除了第一个参数以外的其他参数都有默认值的时候,
  _TransformBuilder(const _TransformBuilder &) = delete; // 禁止拷贝构造
  _TransformBuilder &operator=(const _TransformBuilder &) = delete;// 禁用赋值运算符

  BUILDER_DEFINE_FIELD(const QPointF &, setPos)
  BUILDER_DEFINE_FIELD(int, setType)

 public:
  virtual void build(Target *transform) {
    BUILDER_BUILD(setPos);
    BUILDER_BUILD(setType);
  }
  Transform *build() {
    auto transform = new Target();
    build(transform);
    return (Transform *)transform;
  }

  void addToGameObject(GameObject *gameObject) {
    gameObject->addComponent(build());
  }
};

class TransformBuilder;
class TransformBuilder : public _TransformBuilder<TransformBuilder, Transform> {
};

class ImageTransformBuilder;
class ImageTransformBuilder
    : public _TransformBuilder<ImageTransformBuilder, ImageTransform> {
  BUILDER_DEFINE_FIELD(const char *, setImage)
  BUILDER_DEFINE_FIELD(const QPointF &, setOffset) // QPointF：使用浮点精度定义平面中的点
  BUILDER_DEFINE_FIELD(Qt::Alignment, setAlignment)

 public:
  virtual void build(Target *transform) override {
    _TransformBuilder<ImageTransformBuilder, ImageTransform>::build(transform);
    BUILDER_BUILD(setImage);
    BUILDER_BUILD(setOffset);
    BUILDER_BUILD(setAlignment);
  }
  Transform *build() {
    auto transform = new Target();
    build(transform);
    return (Transform *)transform;
  }
};

#endif  // TRANSFORMBUILDER_H
