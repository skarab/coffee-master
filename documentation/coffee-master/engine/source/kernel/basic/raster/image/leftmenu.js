function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6292\" class=\"headerLeftMenuInActive\"><a id=\"aID6292\" href=\"#\" OnMouseOver=\"link('_dir','image0',this)\" class=\"leftMenuLinkHeadInActive\">image</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID756\" class=\"leftMenuInActive\"><a id=\"aID756\" href=\"#\" OnMouseOver=\"link('_class','Image39014',this)\" class=\"leftMenuLinkInActive\">Image</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
