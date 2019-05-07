module quicksort
    implicit none
    private

    interface sort
        module procedure isort, rsort
    end interface sort

    public :: sort
contains
    subroutine isort(array, index_array)
        integer, intent(inout) :: array(:)
        integer, intent(out), optional :: index_array(:)
        integer :: n

        n = size(array)
        if (present(index_array)) index_array = iota(n)
        call iquicksort(array, n, 1, n, index_array)
    end subroutine isort

    subroutine rsort(array, index_array)
        real, intent(inout) :: array(:)
        integer, intent(out), optional :: index_array(:)
        integer :: n

        n = size(array)
        if (present(index_array)) index_array = iota(n)
        call rquicksort(array, n, 1, n, index_array)
    end subroutine rsort

    recursive subroutine iquicksort(a, n, lo, hi, ia)
        integer, intent(inout) :: a(n)
        integer, intent(in) :: n, lo, hi
        integer, intent(inout), optional :: ia(n)
        integer :: p

        if (lo < hi) then
            p = ipartition(a, n, lo, hi, ia)
            call iquicksort(a, n, lo, p - 1, ia)
            call iquicksort(a, n, p + 1, hi, ia)
        end if
    end subroutine iquicksort

    recursive subroutine rquicksort(a, n, lo, hi, ia)
        real, intent(inout) :: a(n)
        integer, intent(in) :: n, lo, hi
        integer, intent(inout), optional :: ia(n)
        integer :: p

        if (lo < hi) then
            p = rpartition(a, n, lo, hi, ia)
            call rquicksort(a, n, lo, p - 1, ia)
            call rquicksort(a, n, p + 1, hi, ia)
        end if
    end subroutine rquicksort

    function ipartition(a, n, lo, hi, ia) result(p)
        integer, intent(inout) :: a(n)
        integer, intent(in) :: n, lo, hi
        integer, intent(inout), optional :: ia(n)
        integer :: pivot
        integer :: i, j, p

        pivot = imedian3(a, n, lo, hi, ia)
        i = lo - 1
        j = hi
        do
            do
                i = i + 1
                if (a(i) >= pivot) exit
            end do
            do
                j = j - 1
                if (a(j) <= pivot) exit
            end do
            if (i >= j) exit
            call iswap(a(i), a(j))
            if (present(ia)) call iswap(ia(i), ia(j))
        end do
        call iswap(a(i), a(hi))
        if (present(ia)) call iswap(ia(i), ia(hi))
        p = i
    end function ipartition

    function rpartition(a, n, lo, hi, ia) result(p)
        real, intent(inout) :: a(n)
        integer, intent(in) :: n, lo, hi
        integer, intent(inout), optional :: ia(n)
        real :: pivot
        integer :: i, j, p

        pivot = rmedian3(a, n, lo, hi, ia)
        i = lo - 1
        j = hi
        do
            do
                i = i + 1
                if (a(i) >= pivot) exit
            end do
            do
                j = j - 1
                if (a(j) <= pivot) exit
            end do
            if (i >= j) exit
            call rswap(a(i), a(j))
            if (present(ia)) call iswap(ia(i), ia(j))
        end do
        call rswap(a(i), a(hi))
        if (present(ia)) call iswap(ia(i), ia(hi))
        p = i
    end function rpartition

    integer function imedian3(a, n, lo, hi, ia) result(pivot)
        integer, intent(inout) :: a(n)
        integer, intent(in) :: n, lo, hi
        integer, intent(inout), optional :: ia(n)
        integer :: mid

        mid = lo + (hi - lo) / 2
        if (a(lo) > a(mid)) then
            call iswap(a(lo), a(mid))
            if (present(ia)) call iswap(ia(lo), ia(mid))
        end if
        if (a(lo) > a(hi)) then
            call iswap(a(lo), a(hi))
            if (present(ia)) call iswap(ia(lo), ia(hi))
        end if
        if (a(mid) > a(hi)) then
            call iswap(a(mid), a(hi))
            if (present(ia)) call iswap(ia(mid), ia(hi))
        end if
        pivot = a(hi)
    end function imedian3

    real function rmedian3(a, n, lo, hi, ia) result(pivot)
        real, intent(inout) :: a(n)
        integer, intent(in) :: n, lo, hi
        integer, intent(inout), optional :: ia(n)
        integer :: mid

        mid = lo + (hi - lo) / 2
        if (a(lo) > a(mid)) then
            call rswap(a(lo), a(mid))
            if (present(ia)) call iswap(ia(lo), ia(mid))
        end if
        if (a(lo) > a(hi)) then
            call rswap(a(lo), a(hi))
            if (present(ia)) call iswap(ia(lo), ia(hi))
        end if
        if (a(mid) > a(hi)) then
            call rswap(a(mid), a(hi))
            if (present(ia)) call iswap(ia(mid), ia(hi))
        end if
        pivot = a(hi)
    end function rmedian3

    pure function iota(n) result(a)
        integer, intent(in) :: n
        integer :: i, a(n)

        do i = 1, n
            a(i) = i
        end do
    end function iota

    elemental subroutine iswap(i, j)
        integer, intent(inout) :: i, j
        integer :: tmp

        tmp = i
        i = j
        j = tmp
    end subroutine iswap

    elemental subroutine rswap(r, s)
        real, intent(inout) :: r, s
        real :: tmp

        tmp = r
        r = s
        s = tmp
    end subroutine rswap
end module quicksort
