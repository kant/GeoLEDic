#ifndef ShapesFromNotes_hpp
#define ShapesFromNotes_hpp

#include "Controls.hpp"
#include "MidiDefs.hpp"
#include "DomeDefs.hpp"
#include <map>

class ShapesFromNotes: public Controls
{
public:
   enum Shape {
      SHAPE_TRIANGLE = 0,
      SHAPE_PENTAGON = 1,
      SHAPE_BLOB = 2
   };
   
   ShapesFromNotes();
   virtual void noteOn(uint8_t note, uint8_t velocity, uint8_t channel);
   virtual void noteOff(uint8_t note, uint8_t channel);
   
   uint8_t getTriangleValue(uint8_t note) const;
   
private:
   void setBlob(uint8_t note, uint8_t velocity);
   void setPentagon(uint8_t note, uint8_t velocity);

   void associateShapeWithTriangle(Shape shape_type, uint8_t shape_id, uint8_t note, uint8_t velocity);
   void dissociateShapeFromTriangle(Shape shape_type, uint8_t shape_id, uint8_t note);

   enum PrivateConsts {
      MAX_ASSOCIATIONS = 4
   };
   
   struct Association {
      Association();
      Association(Shape shape_type, uint8_t shape_id, uint8_t velocity);
      
      Shape shape_type;
      uint8_t shape_id;
      uint8_t velocity;
   };
   
   struct Associations
   {
      Associations();
      
      void set(const Association& association);
      void clear(Shape shape_type, uint8_t shape_id);

      uint8_t velocity() const;
      
      uint8_t num_associations;
      Association associations[MAX_ASSOCIATIONS];
   };
   
   std::map<uint8_t, Associations> m_triangle_associations;
   uint8_t m_triangles[DOME_NUM_TRIANGLES];
};

#endif /* ShapesFromNotes_hpp */
