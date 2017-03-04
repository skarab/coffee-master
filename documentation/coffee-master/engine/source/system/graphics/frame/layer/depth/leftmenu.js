function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6359\" class=\"headerLeftMenuInActive\"><a id=\"aID6359\" href=\"#\" OnMouseOver=\"link('_dir','depth0',this)\" class=\"leftMenuLinkHeadInActive\">depth</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID862\" class=\"leftMenuInActive\"><a id=\"aID862\" href=\"#\" OnMouseOver=\"link('_class','FrameLayerDepth54809',this)\" class=\"leftMenuLinkInActive\">FrameLayerDepth</a></div>\n");
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
