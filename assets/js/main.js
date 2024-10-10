$(document).ready(function() {
	
    /* ===== Stickyfill ===== */
    /* Ref: https://github.com/wilddeer/stickyfill */
    // Add browser support to position: sticky
    var elements = $('.sticky');
    Stickyfill.add(elements);


    /* Activate scrollspy menu */
    $('body').scrollspy({target: '#doc-menu', offset: 100});
    
    /* Smooth scrolling */
	$('a.scrollto').on('click', function(e){
        //store hash
        var target = this.hash;    
        e.preventDefault();
		$('body').scrollTo(target, 800, {offset: 0, 'axis':'y'});
		
	});
     
    /* Bootstrap lightbox */
    /* Ref: http://ashleydw.github.io/lightbox/ */

    $(document).delegate('*[data-toggle="lightbox"]', 'click', function(e) {
        e.preventDefault();
        $(this).ekkoLightbox();
    });    


});

function copyCode(id) {
    const codeElement = document.getElementById(id);
    
    if (!codeElement) {
        console.error("Element with id " + id + " not found.");
        return;
    }

    let codeText = codeElement.innerText.replace(/\u00A0/g, ' '); // Replace &nbsp; with space

    navigator.clipboard.writeText(codeText).then(() => {
        const copyButton = codeElement.nextElementSibling; // Assuming the button is the next sibling
        
        // Change the icon/text to indicate it was copied
        copyButton.innerHTML = '<i class="fas fa-check"></i> Copied!';
        
        // Reset the button back to original after 2 seconds
        setTimeout(() => {
            copyButton.innerHTML = '<i class="far fa-clipboard"></i> Copy code';
        }, 2000);
    }).catch(err => {
        console.error("Failed to copy: ", err);
    });
}
document.getElementById("downloadLinkPg").addEventListener("click", function(event) {
    event.preventDefault();
    const url = this.href;
    const fileName = "PowerGadget_3.6.msi";

    fetch(url)
      .then(response => response.blob())
      .then(blob => {
        const link = document.createElement("a");
        link.href = window.URL.createObjectURL(blob);
        link.download = fileName;
        link.click();
      })
      .catch(console.error);
  });
document.getElementById("downloadLinksh").addEventListener("click", function(event) {
    event.preventDefault();
    const url = this.href;
    const fileName = "installer.sh";

    fetch(url)
      .then(response => response.blob())
      .then(blob => {
        const link = document.createElement("a");
        link.href = window.URL.createObjectURL(blob);
        link.download = fileName;
        link.click();
      })
      .catch(console.error);
  });
document.getElementById("downloadLinkbat").addEventListener("click", function(event) {
    event.preventDefault();
    const url = this.href;
    const fileName = "installer.bat";

    fetch(url)
    .then(response => response.blob())
    .then(blob => {
        const link = document.createElement("a");
        link.href = window.URL.createObjectURL(blob);
        link.download = fileName;
        link.click();
    })
    .catch(console.error);
});