#ifndef TESTS_PLUGINS_DERIVEDFROMBASETRANSFORM_H_
#define TESTS_PLUGINS_DERIVEDFROMBASETRANSFORM_H_

#include <gst/gst.h>
#include <glibmm.h>
#include <gstreamermm.h>
// #include <gstreamermm/basetransform.h>
#include <gstreamermm/private/basetransform_p.h>
#include <assert.h>

class DerivedFromBaseTransform : public Gst::BaseTransform
{
public:
    static void class_init(Gst::ElementClass<DerivedFromBaseTransform> *klass);
    explicit DerivedFromBaseTransform(GstBaseTransform *gobj);

    Gst::FlowReturn
    transform_ip_vfunc(const Glib::RefPtr<Gst::Buffer>& buf);

    Glib::PropertyProxy<int>
    property_test() { return prop_test.get_proxy(); }

    static bool register_element(Glib::RefPtr<Gst::Plugin> plugin);

private:
    Glib::Property<int> prop_test;
};

#endif /* TESTS_PLUGINS_DERIVEDFROMBASETRANSFORM_H_ */
