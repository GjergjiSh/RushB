// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtoModuleInterface.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ProtoModuleInterface_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ProtoModuleInterface_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017003 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ProtoModuleInterface_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ProtoModuleInterface_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ProtoModuleInterface_2eproto;
class ServoValues_Proto;
struct ServoValues_ProtoDefaultTypeInternal;
extern ServoValues_ProtoDefaultTypeInternal _ServoValues_Proto_default_instance_;
class SharedData_Proto;
struct SharedData_ProtoDefaultTypeInternal;
extern SharedData_ProtoDefaultTypeInternal _SharedData_Proto_default_instance_;
class UltraSonicValues_Proto;
struct UltraSonicValues_ProtoDefaultTypeInternal;
extern UltraSonicValues_ProtoDefaultTypeInternal _UltraSonicValues_Proto_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::ServoValues_Proto* Arena::CreateMaybeMessage<::ServoValues_Proto>(Arena*);
template<> ::SharedData_Proto* Arena::CreateMaybeMessage<::SharedData_Proto>(Arena*);
template<> ::UltraSonicValues_Proto* Arena::CreateMaybeMessage<::UltraSonicValues_Proto>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class ServoValues_Proto final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:ServoValues_Proto) */ {
 public:
  inline ServoValues_Proto() : ServoValues_Proto(nullptr) {}
  ~ServoValues_Proto() override;
  explicit constexpr ServoValues_Proto(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ServoValues_Proto(const ServoValues_Proto& from);
  ServoValues_Proto(ServoValues_Proto&& from) noexcept
    : ServoValues_Proto() {
    *this = ::std::move(from);
  }

  inline ServoValues_Proto& operator=(const ServoValues_Proto& from) {
    CopyFrom(from);
    return *this;
  }
  inline ServoValues_Proto& operator=(ServoValues_Proto&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ServoValues_Proto& default_instance() {
    return *internal_default_instance();
  }
  static inline const ServoValues_Proto* internal_default_instance() {
    return reinterpret_cast<const ServoValues_Proto*>(
               &_ServoValues_Proto_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ServoValues_Proto& a, ServoValues_Proto& b) {
    a.Swap(&b);
  }
  inline void Swap(ServoValues_Proto* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ServoValues_Proto* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ServoValues_Proto* New() const final {
    return new ServoValues_Proto();
  }

  ServoValues_Proto* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ServoValues_Proto>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ServoValues_Proto& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const ServoValues_Proto& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ServoValues_Proto* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "ServoValues_Proto";
  }
  protected:
  explicit ServoValues_Proto(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kTopServoFieldNumber = 1,
    kRightServoFieldNumber = 2,
    kLeftServoFieldNumber = 3,
  };
  // int32 top_servo = 1;
  void clear_top_servo();
  ::PROTOBUF_NAMESPACE_ID::int32 top_servo() const;
  void set_top_servo(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_top_servo() const;
  void _internal_set_top_servo(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // int32 right_servo = 2;
  void clear_right_servo();
  ::PROTOBUF_NAMESPACE_ID::int32 right_servo() const;
  void set_right_servo(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_right_servo() const;
  void _internal_set_right_servo(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // int32 left_servo = 3;
  void clear_left_servo();
  ::PROTOBUF_NAMESPACE_ID::int32 left_servo() const;
  void set_left_servo(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_left_servo() const;
  void _internal_set_left_servo(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:ServoValues_Proto)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::int32 top_servo_;
  ::PROTOBUF_NAMESPACE_ID::int32 right_servo_;
  ::PROTOBUF_NAMESPACE_ID::int32 left_servo_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ProtoModuleInterface_2eproto;
};
// -------------------------------------------------------------------

class UltraSonicValues_Proto final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:UltraSonicValues_Proto) */ {
 public:
  inline UltraSonicValues_Proto() : UltraSonicValues_Proto(nullptr) {}
  ~UltraSonicValues_Proto() override;
  explicit constexpr UltraSonicValues_Proto(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  UltraSonicValues_Proto(const UltraSonicValues_Proto& from);
  UltraSonicValues_Proto(UltraSonicValues_Proto&& from) noexcept
    : UltraSonicValues_Proto() {
    *this = ::std::move(from);
  }

  inline UltraSonicValues_Proto& operator=(const UltraSonicValues_Proto& from) {
    CopyFrom(from);
    return *this;
  }
  inline UltraSonicValues_Proto& operator=(UltraSonicValues_Proto&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const UltraSonicValues_Proto& default_instance() {
    return *internal_default_instance();
  }
  static inline const UltraSonicValues_Proto* internal_default_instance() {
    return reinterpret_cast<const UltraSonicValues_Proto*>(
               &_UltraSonicValues_Proto_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(UltraSonicValues_Proto& a, UltraSonicValues_Proto& b) {
    a.Swap(&b);
  }
  inline void Swap(UltraSonicValues_Proto* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(UltraSonicValues_Proto* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline UltraSonicValues_Proto* New() const final {
    return new UltraSonicValues_Proto();
  }

  UltraSonicValues_Proto* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<UltraSonicValues_Proto>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const UltraSonicValues_Proto& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const UltraSonicValues_Proto& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(UltraSonicValues_Proto* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "UltraSonicValues_Proto";
  }
  protected:
  explicit UltraSonicValues_Proto(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDistanceFieldNumber = 1,
  };
  // float distance = 1;
  void clear_distance();
  float distance() const;
  void set_distance(float value);
  private:
  float _internal_distance() const;
  void _internal_set_distance(float value);
  public:

  // @@protoc_insertion_point(class_scope:UltraSonicValues_Proto)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  float distance_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ProtoModuleInterface_2eproto;
};
// -------------------------------------------------------------------

class SharedData_Proto final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:SharedData_Proto) */ {
 public:
  inline SharedData_Proto() : SharedData_Proto(nullptr) {}
  ~SharedData_Proto() override;
  explicit constexpr SharedData_Proto(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SharedData_Proto(const SharedData_Proto& from);
  SharedData_Proto(SharedData_Proto&& from) noexcept
    : SharedData_Proto() {
    *this = ::std::move(from);
  }

  inline SharedData_Proto& operator=(const SharedData_Proto& from) {
    CopyFrom(from);
    return *this;
  }
  inline SharedData_Proto& operator=(SharedData_Proto&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const SharedData_Proto& default_instance() {
    return *internal_default_instance();
  }
  static inline const SharedData_Proto* internal_default_instance() {
    return reinterpret_cast<const SharedData_Proto*>(
               &_SharedData_Proto_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(SharedData_Proto& a, SharedData_Proto& b) {
    a.Swap(&b);
  }
  inline void Swap(SharedData_Proto* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SharedData_Proto* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline SharedData_Proto* New() const final {
    return new SharedData_Proto();
  }

  SharedData_Proto* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<SharedData_Proto>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const SharedData_Proto& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const SharedData_Proto& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SharedData_Proto* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "SharedData_Proto";
  }
  protected:
  explicit SharedData_Proto(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kServosFieldNumber = 1,
    kUssFieldNumber = 2,
  };
  // .ServoValues_Proto servos = 1;
  bool has_servos() const;
  private:
  bool _internal_has_servos() const;
  public:
  void clear_servos();
  const ::ServoValues_Proto& servos() const;
  PROTOBUF_MUST_USE_RESULT ::ServoValues_Proto* release_servos();
  ::ServoValues_Proto* mutable_servos();
  void set_allocated_servos(::ServoValues_Proto* servos);
  private:
  const ::ServoValues_Proto& _internal_servos() const;
  ::ServoValues_Proto* _internal_mutable_servos();
  public:
  void unsafe_arena_set_allocated_servos(
      ::ServoValues_Proto* servos);
  ::ServoValues_Proto* unsafe_arena_release_servos();

  // .UltraSonicValues_Proto uss = 2;
  bool has_uss() const;
  private:
  bool _internal_has_uss() const;
  public:
  void clear_uss();
  const ::UltraSonicValues_Proto& uss() const;
  PROTOBUF_MUST_USE_RESULT ::UltraSonicValues_Proto* release_uss();
  ::UltraSonicValues_Proto* mutable_uss();
  void set_allocated_uss(::UltraSonicValues_Proto* uss);
  private:
  const ::UltraSonicValues_Proto& _internal_uss() const;
  ::UltraSonicValues_Proto* _internal_mutable_uss();
  public:
  void unsafe_arena_set_allocated_uss(
      ::UltraSonicValues_Proto* uss);
  ::UltraSonicValues_Proto* unsafe_arena_release_uss();

  // @@protoc_insertion_point(class_scope:SharedData_Proto)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::ServoValues_Proto* servos_;
  ::UltraSonicValues_Proto* uss_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ProtoModuleInterface_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ServoValues_Proto

// int32 top_servo = 1;
inline void ServoValues_Proto::clear_top_servo() {
  top_servo_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ServoValues_Proto::_internal_top_servo() const {
  return top_servo_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ServoValues_Proto::top_servo() const {
  // @@protoc_insertion_point(field_get:ServoValues_Proto.top_servo)
  return _internal_top_servo();
}
inline void ServoValues_Proto::_internal_set_top_servo(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  top_servo_ = value;
}
inline void ServoValues_Proto::set_top_servo(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_top_servo(value);
  // @@protoc_insertion_point(field_set:ServoValues_Proto.top_servo)
}

// int32 right_servo = 2;
inline void ServoValues_Proto::clear_right_servo() {
  right_servo_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ServoValues_Proto::_internal_right_servo() const {
  return right_servo_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ServoValues_Proto::right_servo() const {
  // @@protoc_insertion_point(field_get:ServoValues_Proto.right_servo)
  return _internal_right_servo();
}
inline void ServoValues_Proto::_internal_set_right_servo(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  right_servo_ = value;
}
inline void ServoValues_Proto::set_right_servo(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_right_servo(value);
  // @@protoc_insertion_point(field_set:ServoValues_Proto.right_servo)
}

// int32 left_servo = 3;
inline void ServoValues_Proto::clear_left_servo() {
  left_servo_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ServoValues_Proto::_internal_left_servo() const {
  return left_servo_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ServoValues_Proto::left_servo() const {
  // @@protoc_insertion_point(field_get:ServoValues_Proto.left_servo)
  return _internal_left_servo();
}
inline void ServoValues_Proto::_internal_set_left_servo(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  left_servo_ = value;
}
inline void ServoValues_Proto::set_left_servo(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_left_servo(value);
  // @@protoc_insertion_point(field_set:ServoValues_Proto.left_servo)
}

// -------------------------------------------------------------------

// UltraSonicValues_Proto

// float distance = 1;
inline void UltraSonicValues_Proto::clear_distance() {
  distance_ = 0;
}
inline float UltraSonicValues_Proto::_internal_distance() const {
  return distance_;
}
inline float UltraSonicValues_Proto::distance() const {
  // @@protoc_insertion_point(field_get:UltraSonicValues_Proto.distance)
  return _internal_distance();
}
inline void UltraSonicValues_Proto::_internal_set_distance(float value) {
  
  distance_ = value;
}
inline void UltraSonicValues_Proto::set_distance(float value) {
  _internal_set_distance(value);
  // @@protoc_insertion_point(field_set:UltraSonicValues_Proto.distance)
}

// -------------------------------------------------------------------

// SharedData_Proto

// .ServoValues_Proto servos = 1;
inline bool SharedData_Proto::_internal_has_servos() const {
  return this != internal_default_instance() && servos_ != nullptr;
}
inline bool SharedData_Proto::has_servos() const {
  return _internal_has_servos();
}
inline void SharedData_Proto::clear_servos() {
  if (GetArenaForAllocation() == nullptr && servos_ != nullptr) {
    delete servos_;
  }
  servos_ = nullptr;
}
inline const ::ServoValues_Proto& SharedData_Proto::_internal_servos() const {
  const ::ServoValues_Proto* p = servos_;
  return p != nullptr ? *p : reinterpret_cast<const ::ServoValues_Proto&>(
      ::_ServoValues_Proto_default_instance_);
}
inline const ::ServoValues_Proto& SharedData_Proto::servos() const {
  // @@protoc_insertion_point(field_get:SharedData_Proto.servos)
  return _internal_servos();
}
inline void SharedData_Proto::unsafe_arena_set_allocated_servos(
    ::ServoValues_Proto* servos) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(servos_);
  }
  servos_ = servos;
  if (servos) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:SharedData_Proto.servos)
}
inline ::ServoValues_Proto* SharedData_Proto::release_servos() {
  
  ::ServoValues_Proto* temp = servos_;
  servos_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::ServoValues_Proto* SharedData_Proto::unsafe_arena_release_servos() {
  // @@protoc_insertion_point(field_release:SharedData_Proto.servos)
  
  ::ServoValues_Proto* temp = servos_;
  servos_ = nullptr;
  return temp;
}
inline ::ServoValues_Proto* SharedData_Proto::_internal_mutable_servos() {
  
  if (servos_ == nullptr) {
    auto* p = CreateMaybeMessage<::ServoValues_Proto>(GetArenaForAllocation());
    servos_ = p;
  }
  return servos_;
}
inline ::ServoValues_Proto* SharedData_Proto::mutable_servos() {
  ::ServoValues_Proto* _msg = _internal_mutable_servos();
  // @@protoc_insertion_point(field_mutable:SharedData_Proto.servos)
  return _msg;
}
inline void SharedData_Proto::set_allocated_servos(::ServoValues_Proto* servos) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete servos_;
  }
  if (servos) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<::ServoValues_Proto>::GetOwningArena(servos);
    if (message_arena != submessage_arena) {
      servos = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, servos, submessage_arena);
    }
    
  } else {
    
  }
  servos_ = servos;
  // @@protoc_insertion_point(field_set_allocated:SharedData_Proto.servos)
}

// .UltraSonicValues_Proto uss = 2;
inline bool SharedData_Proto::_internal_has_uss() const {
  return this != internal_default_instance() && uss_ != nullptr;
}
inline bool SharedData_Proto::has_uss() const {
  return _internal_has_uss();
}
inline void SharedData_Proto::clear_uss() {
  if (GetArenaForAllocation() == nullptr && uss_ != nullptr) {
    delete uss_;
  }
  uss_ = nullptr;
}
inline const ::UltraSonicValues_Proto& SharedData_Proto::_internal_uss() const {
  const ::UltraSonicValues_Proto* p = uss_;
  return p != nullptr ? *p : reinterpret_cast<const ::UltraSonicValues_Proto&>(
      ::_UltraSonicValues_Proto_default_instance_);
}
inline const ::UltraSonicValues_Proto& SharedData_Proto::uss() const {
  // @@protoc_insertion_point(field_get:SharedData_Proto.uss)
  return _internal_uss();
}
inline void SharedData_Proto::unsafe_arena_set_allocated_uss(
    ::UltraSonicValues_Proto* uss) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(uss_);
  }
  uss_ = uss;
  if (uss) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:SharedData_Proto.uss)
}
inline ::UltraSonicValues_Proto* SharedData_Proto::release_uss() {
  
  ::UltraSonicValues_Proto* temp = uss_;
  uss_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::UltraSonicValues_Proto* SharedData_Proto::unsafe_arena_release_uss() {
  // @@protoc_insertion_point(field_release:SharedData_Proto.uss)
  
  ::UltraSonicValues_Proto* temp = uss_;
  uss_ = nullptr;
  return temp;
}
inline ::UltraSonicValues_Proto* SharedData_Proto::_internal_mutable_uss() {
  
  if (uss_ == nullptr) {
    auto* p = CreateMaybeMessage<::UltraSonicValues_Proto>(GetArenaForAllocation());
    uss_ = p;
  }
  return uss_;
}
inline ::UltraSonicValues_Proto* SharedData_Proto::mutable_uss() {
  ::UltraSonicValues_Proto* _msg = _internal_mutable_uss();
  // @@protoc_insertion_point(field_mutable:SharedData_Proto.uss)
  return _msg;
}
inline void SharedData_Proto::set_allocated_uss(::UltraSonicValues_Proto* uss) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete uss_;
  }
  if (uss) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<::UltraSonicValues_Proto>::GetOwningArena(uss);
    if (message_arena != submessage_arena) {
      uss = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, uss, submessage_arena);
    }
    
  } else {
    
  }
  uss_ = uss;
  // @@protoc_insertion_point(field_set_allocated:SharedData_Proto.uss)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ProtoModuleInterface_2eproto