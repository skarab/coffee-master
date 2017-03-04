function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6358\" class=\"headerLeftMenuInActive\"><a id=\"aID6358\" href=\"#\" OnMouseOver=\"link('_dir','bgra0',this)\" class=\"leftMenuLinkHeadInActive\">bgra</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID861\" class=\"leftMenuInActive\"><a id=\"aID861\" href=\"#\" OnMouseOver=\"link('_class','FrameLayerBGRA54809',this)\" class=\"leftMenuLinkInActive\">FrameLayerBGRA</a></div>\n");
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
