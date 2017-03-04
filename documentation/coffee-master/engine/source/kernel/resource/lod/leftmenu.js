function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6318\" class=\"headerLeftMenuInActive\"><a id=\"aID6318\" href=\"#\" OnMouseOver=\"link('_dir','lod0',this)\" class=\"leftMenuLinkHeadInActive\">lod</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID801\" class=\"leftMenuInActive\"><a id=\"aID801\" href=\"#\" OnMouseOver=\"link('_class','LOD24579',this)\" class=\"leftMenuLinkInActive\">LOD</a></div>\n");
document.write("<div id=\"divID802\" class=\"leftMenuInActive\"><a id=\"aID802\" href=\"#\" OnMouseOver=\"link('_class','LODParameters24579',this)\" class=\"leftMenuLinkInActive\">LODParameters</a></div>\n");
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
