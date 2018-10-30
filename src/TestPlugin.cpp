#include "TestPlugin.h"

void
DerivedFromBaseTransform::class_init(Gst::ElementClass<DerivedFromBaseTransform> *klass)
{
    klass->set_metadata("derivedfrombasetransform_longname",
    "derivedfrombasetransform_classification",
    "derivedfrombasetransform_detail_description",
    "derivedfrombasetransform_detail_author");

    klass->add_pad_template(Gst::PadTemplate::create("sink", Gst::PAD_SINK, Gst::PAD_ALWAYS, Gst::Caps::create_any()));
    klass->add_pad_template(Gst::PadTemplate::create("src", Gst::PAD_SRC, Gst::PAD_ALWAYS, Gst::Caps::create_any()));
}

DerivedFromBaseTransform::DerivedFromBaseTransform(GstBaseTransform *gobj)
 : Glib::ObjectBase(typeid (DerivedFromBaseTransform)) // type must be registered before use
 , Gst::BaseTransform(gobj)
 , prop_test(*this, "test", 10, "Nick", "Blurb", Glib::PARAM_READWRITE)
{
    set_passthrough(true);
}

Gst::FlowReturn
DerivedFromBaseTransform::transform_ip_vfunc(const Glib::RefPtr<Gst::Buffer>& buf)
{

}

bool
DerivedFromBaseTransform::register_element(Glib::RefPtr<Gst::Plugin> plugin)
{
    return Gst::ElementFactory::register_element(plugin, "derivedfrombasetransform", GST_RANK_NONE, Gst::register_mm_type<DerivedFromBaseTransform>("derivedfrombasetransform"));
}
