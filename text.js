let cartCount = 0;

function addToCart(productId) {
    cartCount++;
    document.getElementById('cart-count').innerText = cartCount;
    alert('Product added to cart!');
}
