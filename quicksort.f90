module quicksort
    implicit none
    private
    public :: sort

    interface sort
        module procedure isort, rsort
    end interface sort

    interface
        module subroutine isort(array, index_array)
            use, intrinsic :: iso_fortran_env, only: int32, int64
            integer(int32), intent(inout) :: array(:)
            integer(int64), intent(out), optional :: index_array(:)
        end subroutine isort

        module subroutine rsort(array, index_array)
            use, intrinsic :: iso_fortran_env, only: int64, real32
            real(real32), intent(inout) :: array(:)
            integer(int64), intent(out), optional :: index_array(:)
        end subroutine rsort
    end interface

    interface
        subroutine c_fsort(a, n, ip) bind(c, name='fsort')
            use, intrinsic :: iso_c_binding, only: c_float, c_size_t
            real(c_float), intent(inout) :: a(*)
            integer(c_size_t), value, intent(in) :: n
            integer(c_size_t), intent(inout), optional :: ip(*)
        end subroutine c_fsort

        subroutine c_isort(a, n, ip) bind(c, name='isort')
            use, intrinsic :: iso_c_binding, only: c_int32_t, c_size_t
            integer(c_int32_t), intent(inout) :: a(*)
            integer(c_size_t), value, intent(in) :: n
            integer(c_size_t), intent(inout), optional :: ip(*)
        end subroutine c_isort
    end interface
end module quicksort

submodule (quicksort) isort_impl
    use, intrinsic :: iso_fortran_env, only: int64

    integer(int64) :: n
contains
    module procedure isort
        n = size(array)
        call c_isort(array, n, index_array)
        if (present(index_array)) index_array = index_array + 1
    end procedure isort
end submodule isort_impl

submodule (quicksort) rsort_impl
    use, intrinsic :: iso_fortran_env, only: int64

    integer(int64) :: n
contains
    module procedure rsort
        n = size(array)
        call c_fsort(array, n, index_array)
        if (present(index_array)) index_array = index_array + 1
    end procedure rsort
end submodule rsort_impl
