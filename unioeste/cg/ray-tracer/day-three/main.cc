//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "camera.h"
#include "constant_medium.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "quad.h"
#include "sphere.h"
#include "bvh.h"

camera getCamera(int camNum) {
    camera cam;

    cam.aspect_ratio = 1.0;
    cam.image_width = 200;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;
    cam.background = color(0.70, 0.80, 1.00) * 0.5;

    cam.vfov = 90;
    cam.lookfrom = point3(0, 250, -400);
    cam.lookat = point3(0, 0,0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0;

    switch (camNum) {
        case 1:
            return cam;
        case 2:
            cam.vfov = 50;
            cam.lookfrom = point3(-300, 500, 500);
            cam.lookat = point3(0, 0,0);
            return cam;
        case 3:
            cam.vfov = 50;
            cam.lookfrom = point3(300, 800, 1000);
            cam.lookat = point3(0, 0,0);
            return cam;
        case 4:
            cam.vfov = 50;
            cam.lookfrom = point3(300, 30, -400);
            cam.lookat = point3(0, 100,100);
            cam.defocus_angle = 5;
            cam.focus_dist = 320;
            return cam;
        case 5:
        default:
            cam.vfov = 90;
            cam.lookfrom = point3(-100, 50, -100);
            cam.lookat = point3(-120, 60,0);
            return cam;
    }
}

int main() {
    hittable_list scene;

    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto orange = make_shared<lambertian>(color(1.0, .4, 0));
    auto dirt = make_shared<lambertian>(make_shared<image_texture>("dirt.png",5,100));

    // Big Sphere
    scene.add(make_shared<sphere>(vec3(0,-5000,0), 5000, dirt));
    scene.add(make_shared<constant_medium>(
                      make_shared<sphere>(
                              vec3(0,-5200,0),
                              5200,
                              dirt),
                      0.5,
                      color(1,0,1)
              )
    );

    // Glass Sphere
    auto glass = make_shared<dielectric>(1.5, color(0,1,1));
    auto bubble = make_shared<dielectric>(1.0/1.5, color(0,1,1));
    scene.add(make_shared<sphere>(vec3(150,60,-150), 60, glass));
    scene.add(make_shared<sphere>(vec3(150,60,-150), 48, bubble));

    // Cube
    auto patter_mix = make_shared<mix>(make_shared<image_texture>("pattern.jpg",0.1,0.1),orange,glass);
    scene.add(make_shared<translate>(
            box(vec3(0,0,0), vec3(-100,100,100), patter_mix),
            vec3(50,0,-50))
    );

    // Tower
    hittable_list tower;
    auto red_metal = make_shared<metal>(color(1, 0.0, 0.0),0.1);
    auto paint_mix = make_shared<mix>(make_shared<image_texture>("paint.jpg",1,1),green, red_metal);
    tower.add(make_shared<sphere>(vec3(-200,80,150), 80, paint_mix));
    auto gold  = make_shared<metal>(color(0.8, 0.6, 0.2),0.8);
    tower.add(make_shared<translate>(
            box(vec3(0,0,0), vec3(-200,25,200), gold),
            vec3(-100,160,50))
    );
    auto wood = make_shared<lambertian>(make_shared<image_texture>("wood.jpg",0.5,0.5));
    tower.add(make_shared<sphere>(vec3(-200,260,150), 80, wood));

    scene.add(make_shared<bvh_node>(tower));

    // Lights
    auto light = make_shared<diffuse_light>(color(15, 15, 15));
    scene.add(make_shared<sphere>(point3(800,700,300),200,light));
    scene.add(make_shared<sphere>(point3(-800,700,-300),100,light));

    hittable_list lights;
    auto m = shared_ptr<material>();
    lights.add(make_shared<sphere>(point3(800,700,200),200,m));
    lights.add(make_shared<sphere>(point3(-800,700,-300),100,m));

    camera cam = getCamera(5);
    cam.render(scene, lights);
}
