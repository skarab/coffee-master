function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6506\" class=\"headerLeftMenuInActive\"><a id=\"aID6506\" href=\"#\" OnMouseOver=\"link('_dir','raster0',this)\" class=\"leftMenuLinkHeadInActive\">raster</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6291\" class=\"leftMenuInActive\"><a id=\"aID6291\" href=\"#\" OnMouseOver=\"link('_dir','color/color0',this)\" class=\"leftMenuLinkInActive\">color</a></div>\n");
document.write("<div id=\"divID6292\" class=\"leftMenuInActive\"><a id=\"aID6292\" href=\"#\" OnMouseOver=\"link('_dir','image/image0',this)\" class=\"leftMenuLinkInActive\">image</a></div>\n");
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
